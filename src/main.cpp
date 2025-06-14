#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <settings.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

using namespace std;

DNSServer dnsServer;
AsyncWebServer server(80);

const char* ssid = SSID;
const char* password = PASSWORD;
const int channel = CHANNEL;
const int brightness = BRIGHTNESS;
const bool hidden = HIDDEN;
const char* displayColor = DISPLAY_COLOR;

const int dataPin = DATA;
const int clkPin = CLK;
const int csPin = CS;

class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}
  
    bool canHandle(AsyncWebServerRequest *request){
      return true;
    }
  
    void handleRequest(AsyncWebServerRequest *request) {
      request->send(LittleFS, "/dist/index.html", "text/html");
    }
  };

U8G2_MAX7219_8X8_F_4W_SW_SPI interface(U8G2_R0, clkPin, dataPin, csPin, U8X8_PIN_NONE, U8X8_PIN_NONE);
class Display{
  protected:
    String color;
    bool displaystate[8][8];
  public:
    Display(String color): color(color) {
      interface.begin();
      interface.setFontMode(1);
      interface.setContrast(brightness*16);
      interface.setBitmapMode(1);
      interface.clearBuffer();
      
      for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
          displaystate[row][col] = false;
        }
      }
    }

    String getColor(){
      return color;
    }

    bool (&getState())[8][8] {
      return displaystate;
    }

    void drawArray(JsonArray display){
      for (int row = 0; row < 8; row++) {
        JsonArray rowArray = display[row].as<JsonArray>();
        for (int col = 0; col < 8; col++) {
          int color = rowArray[col] ? 1 : 0;
          interface.setDrawColor(color);
          interface.drawPixel(col, row);
          displaystate[row][col] = rowArray[col];
        }
      }
      interface.sendBuffer();
    }
};

Display* current; 

void webpage() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/dist/index.html", "text/html");
  }).setFilter(ON_AP_FILTER);

  server.serveStatic("/", LittleFS, "/dist/").setFilter(ON_AP_FILTER);

  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(LittleFS, "/dist/index.html", "text/html");
  });
}

void save_state(Display &current){
  File stateFile = LittleFS.open("/state.json", "w");
  JsonDocument stateDoc;
  bool (&state)[8][8] = current.getState();
  JsonArray arr = stateDoc.to<JsonArray>();
  for (int i = 0; i < 8; ++i) {
    JsonArray row = arr.add<JsonArray>();
    for (int j = 0; j < 8; ++j) {
      row.add(state[i][j]); 
    }
  }

  serializeJson(stateDoc, stateFile);
  stateFile.close();
}

void load_state(Display &current){
  File stateFile = LittleFS.open("/state.json", "r");
  if(!stateFile){
    Serial.println("No file!");
  }
  JsonDocument stateDoc;
  DeserializationError err = deserializeJson(stateDoc, stateFile);
  if(err){
    Serial.print("deserializeJson() ");
    Serial.println(err.c_str());
    return;
  }
  JsonArray arr = stateDoc.as<JsonArray>();
  current.drawArray(arr);
  stateFile.close();
  Serial.println("Loaded state!");
}

void display_state(Display &current){
  server.on("/api/display", HTTP_GET, [&current](AsyncWebServerRequest *request){
    JsonDocument response;
    bool (&state)[8][8] = current.getState();
    JsonArray arr = response.to<JsonArray>();
    for (int i = 0; i < 8; ++i) {
      JsonArray row = arr.add<JsonArray>();
      for (int j = 0; j < 8; ++j) {
        row.add(state[i][j]); 
      }
    }
    String result;
    serializeJson(response, result);
    request->send(200, "application/json", result);
  });
}

void display_update(Display &current){
  server.on("/api/display", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [&current](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    String body;
    for (size_t i = 0; i < len; i++) {
      body += (char)data[i];
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, body);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      request->send(400, "text/plain", "Bad Request");
      return;
    }

    if (!doc.is<JsonArray>()) {
      request->send(400, "text/plain", "Expected JSON array");
      return;
    }

    JsonArray display = doc.as<JsonArray>();
    current.drawArray(display);
    save_state(current);
    request->send(200, "text/plain", "Display updated");
  });
}

void display_color(Display &current){
  server.on("/api/display_color", HTTP_GET, [&current](AsyncWebServerRequest *request){
    String color = current.getColor();
    request->send(200, "text/plain", color);
  });
}


void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  if(!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  Serial.println("File system mounted");

  if(!LittleFS.exists("/dist/index.html")) {
    Serial.println("index.html not found");
    return;
  }
  Serial.println("index.html found");

  Serial.println("Initializing display...");
  current = new Display(displayColor);
  Serial.println("Display initialized");

  Serial.println("Loading state...");
  load_state(*current);

  Serial.println("Setting up webpage..");
  webpage();
  display_color(*current);
  display_update(*current);
  display_state(*current);
  Serial.println("Webpage setup complete");

  Serial.print("Setting up AP: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("Channel: ");
  Serial.println(channel);
  Serial.print("Hidden: ");
  Serial.println(hidden ? "true" : "false");
  Serial.println("Starting Access Point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password, channel, hidden);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("AP MAC address: ");
  Serial.println(WiFi.softAPmacAddress());

  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  Serial.println("Starting DNS server...");
  dnsServer.start(53, "*", WiFi.softAPIP());
  Serial.println("DNS server started");

  Serial.println("Starting server...");
  server.begin();
  Serial.println("Server started");
  Serial.println("Setup complete");
}

void loop() {
  dnsServer.processNextRequest();
}
