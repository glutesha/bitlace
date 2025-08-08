#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <settings.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Battery.h>

#include "display/display.h"
#include "display/state/state.h"
#include "settings/settings.h"
#include "server/server.h"
#include "button/button.h"
#include "deepsleep/deepsleep.h"

DNSServer dnsServer;
AsyncWebServer server(80);
JsonDocument settingsDoc;

Display* current = nullptr;
Button* input = nullptr;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Starting...");

  if(!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  Serial.println("File system mounted");

  Serial.println("Loading settings...");
  load_settings(settingsDoc);

  if(!LittleFS.exists("/dist/index.html")) {
    Serial.println("index.html not found");
    return;
  }
  Serial.println("index.html found");

  Serial.println("Initializing display...");
  current = new Display(settingsDoc["color"], settingsDoc["brightness"], settingsDoc["clk"], settingsDoc["data"], settingsDoc["cs"], settingsDoc["flip"]);
  Serial.println("Display initialized");

  Serial.println("Initializing battery...");
  
  static Battery power(3000, 4200, settingsDoc["battery"].as<int>(), 12);
  power.begin(3100, settingsDoc["resistance"].as<double>(), &sigmoidal);
  Serial.println(power.voltage());

  Serial.println("Battery initialized");

  Serial.println("Initializing button...");
  input = new Button(settingsDoc["button"].as<int>());
  setWakeUp(settingsDoc["button"].as<int>());
  Serial.println("Button initialized");

  Serial.println("Loading state...");
  load_state(*current);
  
  Serial.println("Setting up webpage..");
  enable_routes(server, *current, settingsDoc, power);
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
  WiFi.setHostname("bitlace");
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
  if(input->read()){
    current->setBrightness(settingsDoc["brightness"].as<int>());
    sleep();
  }
  current->cue();
}
