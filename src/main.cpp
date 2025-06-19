#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <settings.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include "display/display.h"

using namespace std;

DNSServer dnsServer;
AsyncWebServer server(80);
JsonDocument settingsDoc;

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
  Display current(settingsDoc["color"], settingsDoc["brightness"], settingsDoc["clk"], settingsDoc["data"], settingsDoc["cs"]);
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
