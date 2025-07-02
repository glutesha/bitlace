#include "saves.h"

JsonDocument load_saves(){
    JsonDocument saves;
    File savefile = LittleFS.open("saves.json", FILE_READ);

    if(!savefile){
        return saves;
    }

    deserializeJson(saves, savefile);

    savefile.close();
    return saves;
}

String remove(int id){
    JsonDocument saves = load_saves();
    saves.remove(id);
    
    File savefile = LittleFS.open("saves.json", FILE_WRITE);

    serializeJson(saves, savefile);
    
    savefile.close();
    return "Done";
}   

String save(JsonArray drawing, int id){
    if(LittleFS.totalBytes() - LittleFS.usedBytes() <= drawing.memoryUsage()){
        return "Too few memory to save!";
    }

    JsonDocument saves = load_saves();

    saves[id] = drawing;

    File savefile = LittleFS.open("saves.json", FILE_WRITE);

    serializeJson(saves, savefile);

    savefile.close();
    return "Done";
}