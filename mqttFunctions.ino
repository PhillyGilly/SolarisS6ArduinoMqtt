// mqtt topic structure
// level 1 data
//   -arduino/nano33_1/heartbeat
//   -arduino/nano33_1/status
//   -arduino/nano33_1/moitor
//    etc
// level 2 autodiscovery
//   -homeassistant/sensor/nano33_1/rssi/config
//   
//    etc

// HA ids = nano33_1 and nano33_2

void mqttHeartbeat(){
    String apHex[] = {"f4:92:bf:24:0f:be","18:e8:29:66:1e:0d","e6:63:da:07:68:66","18:e8:29:66:14:22","18:e8:29:67:14:22","18:e8:29:6a:2a:8f"}; 
    String apText[] = {"Bedroom 2","Garden Studio","Hall","Study","Study","Long Range"};
    String apName ="unknown";

    int rssi = -WiFi.RSSI();
    contentStr = "{\"rssi\":\"";
    contentStr += String(rssi); //itoa(rssi, buf, 10);
    contentStr += "\",\"APmac\":\"";
  
    byte bssid[6];
    String bssidAP;
    WiFi.BSSID(bssid); 
    for (int b = 5; b >= 0; b--) {
      if (bssid[b] < 16) {bssidAP += "0";}
      bssidAP += String(bssid[b], HEX);
      if (b > 0) {bssidAP += ":";}
    }
    contentStr += bssidAP; 
    contentStr += "\",\"AP\":\"";
    for (int a = 0; a <= 5; a++) {
      if (apHex[a] == bssidAP){
        apName = apText[a];
        break;
        }
    }
    contentStr += apName; 
    int uptimeMin = (millis() / 1000 / 60);
    int uptimeDay = (uptimeMin / 60/ 24);
    contentStr += "\",\"uptimeMin\":\"";
    contentStr += uptimeMin;
    contentStr += "\",\"uptimeDay\":\"";
    contentStr += uptimeDay;
    contentStr += "\" }";
    topicStr = "arduino/nano33_1/heartbeat";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
}
void mqttStatus(){
    contentStr = "{\"online\":\"1\"}";
    topicStr = "arduino/nano33_1/status";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
}

void mqttData(){
    topicStr = "arduino/nano33_1/monitor";
    contentStr = modbusData();
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
}

void mqttAutoDiscovery(){
    contentStr = "{\"name\":\"Nano33 1 status\",\"uniq_id\":\"Nano33 EM\",\"ic\":\"mdi:gauge\",\"stat_t\":\"arduino/nano33_1/status\",\"val_tpl\":\"{{value_json['online']}}\",\"dev\":{\"name\":\"Nano33 Solis Energy Monitor\",\"sw\":\"2.1.0\",\"mf\":\"Arduino & Phil\",\"mdl\":\"Nano 33\",\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/system/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 RSSI\",\"uniq_id\":\"rssi1\",\"unit_of_meas\":\"%\",\"ic\":\"mdi:access-point\",\"stat_t\":\"arduino/nano33_1/heartbeat\",\"val_tpl\":\"{{value_json.rssi}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/rssi/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 AP\",\"uniq_id\":\"ap1\",\"ic\":\"mdi:access-point\",\"stat_t\":\"arduino/nano33_1/heartbeat\",\"val_tpl\":\"{{value_json.AP}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/ap/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 uptimeDay\",\"uniq_id\":\"uptimeDay1\",\"unit_of_meas\":\"d\",\"ic\":\"mdi:clock-check-outline\",\"stat_t\":\"arduino/nano33_1/heartbeat\",\"val_tpl\":\"{{value_json.uptimeDay}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/uptimeDay/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 uptimeMin\",\"uniq_id\":\"uptimeMin1\",\"unit_of_meas\":\"m\",\"ic\":\"mdi:clock-check-outline\",\"stat_t\":\"arduino/nano33_1/heartbeat\",\"val_tpl\":\"{{value_json.uptimeMin}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/uptimeMin/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 Active Power\", \"uniq_id\":\"activePower1\", \"dev_cla\":\"power\", \"unit_of_meas\":\"W\", \"ic\":\"mdi:flash\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.actP|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/activePower/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 Total Energy\", \"uniq_id\":\"totalEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.totE|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/totalEnergy/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 Energy this month\", \"uniq_id\":\"thismonthEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.tmthE|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/thismonthEnergy/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 Energy last month\", \"uniq_id\":\"lastmonthEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.lmthE|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/lastmonthEnergy/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
    
    contentStr = "{\"name\":\"Nano33 1 Energy today\", \"uniq_id\":\"todayEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.tdyE|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/todayEnergy/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
    
    contentStr = "{\"name\":\"Nano33 1 Energy last day\", \"uniq_id\":\"lastdayEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.ldyE|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/lastdayEnergy/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
    
    contentStr = "{\"name\":\"Nano33 1 Energy this year\", \"uniq_id\":\"thisyearEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.tyE|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/thisyearEnergy/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
    
    contentStr = "{\"name\":\"Nano33 1 Energy last year\", \"uniq_id\":\"lastyearEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.lyE|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/lastyearEnergy/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
    
    contentStr = "{\"name\":\"Nano33 1 DC Voltage\", \"uniq_id\":\"dcVolts1\", \"dev_cla\":\"voltage\", \"unit_of_meas\":\"V\", \"ic\":\"mdi:flash-triangle-outline\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.dcV|round(1)}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/dcVolts/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
    
    contentStr = "{\"name\":\"Nano33 1 DC Amps\", \"uniq_id\":\"dcAmps1\", \"dev_cla\":\"current\", \"unit_of_meas\":\"A\", \"ic\":\"mdi:current-dc\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.dcA|round(1)}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/dcAmps/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 Inverter Temp\", \"uniq_id\":\"inverterTemp1\", \"dev_cla\":\"temperature\", \"unit_of_meas\":\"C\", \"ic\":\"mdi:thermometer\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.invT|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/inverterTemp/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    contentStr = "{\"name\":\"Nano33 1 AC Frequency\", \"uniq_id\":\"acFrequency1\", \"dev_cla\":\"frequency\", \"unit_of_meas\":\"Hz\", \"ic\":\"mdi:sine-wave\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.acHz|round(1)}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/acFrequency/config";
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();
}
    
    void mqttTime(){
    topicStr = "arduino/nano33_1/time";
    contentStr = modbusTime();
    mqttClient.beginMessage(topicStr);
    mqttClient.print(contentStr);
    mqttClient.endMessage();

    }
  
