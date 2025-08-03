#include "settings.h"

void settings_form(AsyncWebServer &server, JsonDocument &settingsDoc){
server.on("/api/settings", HTTP_GET, [&settingsDoc](AsyncWebServerRequest *request){
    File error = LittleFS.open("/dist/error/index.html", "r");
    String response = error.readString();
    
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
      if(request->arg("password").length() < 8){
        response.replace("{ErrorMsg}", "400 Password too short!");
        request->send(400, "text/html", response);
        error.close();
        return;
      }
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
    if(request->hasArg("battery")){
      settingsDoc["battery"] = request->arg("battery").toInt();
    }
    if(request->hasArg("button")){
      settingsDoc["button"] = request->arg("button").toInt();
    }
    if(request->hasArg("resistance")){
      if(request->arg("resistance").toInt() == 0){
        response.replace("{ErrorMsg}", "400 Resistance ratio invalid!");
        request->send(400, "text/html", response);
        error.close();
        return;
      }
      settingsDoc["resistance"] = request->arg("resistance").toInt();
    }
    if(request->hasArg("flip")){
      settingsDoc["flip"] = request->arg("flip").toInt();
    }

    save_settings(settingsDoc);
    error.close();
    ESP.restart();
});}