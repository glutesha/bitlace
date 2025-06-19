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
JsonDocument settingsDoc;

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


class Display{
  protected:
    String color;
    int brightness;
    int clk;
    int data;
    int cs;
    bool displaystate[8][8];
    U8G2_MAX7219_8X8_F_4W_SW_SPI interface;
  public:
    Display(String color, int brightness, int clk, int data, int cs): clk(clk), data(data), cs(cs), interface(U8G2_R0, clk, data, cs, U8X8_PIN_NONE, U8X8_PIN_NONE), color(color), brightness(brightness) {
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

    void setColor(String c){
      color = c;
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
  });

  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/dist/settings/index.html", "text/html");
  });

  server.serveStatic("/", LittleFS, "/dist/");

  server.addHandler(new CaptiveRequestHandler());

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(LittleFS, "/dist/index.html", "text/html");
  });
}

void save_settings(){
  File settingsFile = LittleFS.open("/settings.json", "w");
  serializeJson(settingsDoc, settingsFile);
  settingsFile.close();
}

void load_settings(){
  bool loaderr = false;
  File settingsFile = LittleFS.open("/settings.json", "r");
  if(!settingsFile){
    Serial.println("No file!");
    loaderr = true;
  }
  DeserializationError err = deserializeJson(settingsDoc, settingsFile);
  if(err){
    Serial.print("settings deserializeJson() ");
    Serial.println(err.c_str());
    loaderr = true;
  }
  if(loaderr){
    settingsDoc["ssid"] = SSID;
    settingsDoc["password"] = PASSWORD;
    settingsDoc["hidden"] = HIDDEN;
    settingsDoc["channel"] = CHANNEL;
    settingsDoc["color"] = DISPLAY_COLOR;
    settingsDoc["brightness"] = BRIGHTNESS;
    settingsDoc["data"] = DATA;
    settingsDoc["clk"] = CLK;
    settingsDoc["cs"] = CS;
    return;
  }

  Serial.println("Loaded settings!");
  settingsFile.close();
}


void settings_form(){
  server.on("/api/settings", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->args() == 0){
      String response;
      serializeJson(settingsDoc, response);
      request->send(200, "application/json", response);
      return;
    }

    if(request->hasArg("ssid")){
      settingsDoc["ssid"] = request->arg("ssid").c_str();
    }
    if(request->hasArg("password")){
      settingsDoc["password"] = request->arg("password").c_str();
    }
    if(request->hasArg("channel")){
      settingsDoc["channel"] = request->arg("channel").toInt();
    }
    if(request->hasArg("color")){
      settingsDoc["color"] = request->arg("color").c_str();
    }
    if(request->hasArg("brightness")){
      settingsDoc["brightness"] = request->arg("brightness").toInt();
    }
    if(request->hasArg("hidden")){
      if(request->arg("hidden").c_str() == "true"){
        settingsDoc["hidden"] = true;
      }
      else{
        settingsDoc["hidden"] = false;
      }
    }
    if(request->hasArg("data")){
      settingsDoc["data"] = request->arg("data").toInt();
    }
    if(request->hasArg("cs")){
      settingsDoc["cs"] = request->arg("cs").toInt();
    }
    if(request->hasArg("clk")){
      settingsDoc["clk"] = request->arg("clk").toInt();
    }

    save_settings();
    ESP.restart();
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
    return;
  }
  JsonDocument stateDoc;
  DeserializationError err = deserializeJson(stateDoc, stateFile);
  if(err){
    Serial.print("state deserializeJson() ");
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

  Serial.println("Loading settings...");
  load_settings();

  if(!LittleFS.exists("/dist/index.html")) {
    Serial.println("index.html not found");
    return;
  }
  Serial.println("index.html found");
  Serial.println("Initializing display...");
  current = new Display(settingsDoc["color"], settingsDoc["brightness"], settingsDoc["clk"], settingsDoc["data"], settingsDoc["cs"]);
  Serial.println("Display initialized");

  Serial.println("Loading state...");
  load_state(*current);
  
  Serial.println("Setting up webpage..");
  webpage();
  settings_form();
  display_color(*current);
  display_update(*current);
  display_state(*current);
  Serial.println("Webpage setup complete");

  Serial.print("Setting up AP: ");
  Serial.println(settingsDoc["ssid"].as<String>());
  Serial.print("Password: ");
  Serial.println(settingsDoc["password"].as<String>());
  Serial.print("Channel: ");
  Serial.println(settingsDoc["channel"].as<String>());
  Serial.print("Hidden: ");
  Serial.println(settingsDoc["hidden"].as<bool>());
  Serial.println("Starting Access Point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(settingsDoc["ssid"].as<String>(), settingsDoc["password"].as<String>(), settingsDoc["channel"].as<int>(), settingsDoc["hidden"].as<boolean>());
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
