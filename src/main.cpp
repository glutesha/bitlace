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
