#include "settings.h"

void settings_form(AsyncWebServer &server, JsonDocument &settingsDoc){
server.on("/api/settings", HTTP_GET, [&settingsDoc](AsyncWebServerRequest *request){
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
});}