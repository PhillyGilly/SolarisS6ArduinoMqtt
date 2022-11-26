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
    rssi = -WiFi.RSSI();
    nano33HBout = "{\"rssi\":\"";
    nano33HBout += String(rssi); //itoa(rssi, buf, 10);
    nano33HBout += "\",\"APmac\":\"";
  
    byte bssid[6];
    String bssidAP;
    WiFi.BSSID(bssid); 
    for (int b = 5; b >= 0; b--) {
      if (bssid[b] < 16) {bssidAP += "0";}
      bssidAP += String(bssid[b], HEX);
      if (b > 0) { bssidAP += ":"; }
    }
    nano33HBout += bssidAP;
    nano33HBout += "\",\"AP\":\"";
    for (int a = 0; a <= 5; a++) {
      if (apHex[a] == bssidAP){
        apName = apText[a];
        break;
        }
    }
    nano33HBout += apName; 
    uptimeMin = (millis() / 1000 / 60);
    uptimeDay = (uptimeMin / 60/ 24);
    nano33HBout += "\",\"uptimeMin\":\"";
    nano33HBout += uptimeMin;
    nano33HBout += "\",\"uptimeDay\":\"";
    nano33HBout += uptimeDay;
    nano33HBout += "\" }";
    client.publish("arduino/nano33_1/heartbeat", nano33HBout.c_str(), false);
    }

void mqttStatus(){
    contentStr = "{\"online\":\"1\"}";
    topicStr = "arduino/nano33_1/status";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);
    }

void mqttData(){
    contentStr = "{\"activePower\":\"";
    contentStr += activePower;
    contentStr += "\",\"totalEnergy\":\"";
    contentStr += totalEnergy;
    contentStr += "\",\"thismonthEnergy\":\"";
    contentStr += lastmonthEnergy;
    contentStr += "\",\"todayEnergy\":\"";
    contentStr += todayEnergy;
    contentStr += "\",\"lastdayEnergy\":\"";
    contentStr += lastdayEnergy;
    contentStr += "\",\"thisyearEnergy\":\"";
    contentStr += thisyearEnergy;
    contentStr += "\",\"lastyearEnergy\":\"";
    contentStr += lastyearEnergy;
    contentStr += "\",\"dcVolts\":\"";
    contentStr += dcVolts;
    contentStr += "\",\"dcAmps\":\"";
    contentStr += dcAmps;
    contentStr += "\",\"inverterTemp\":\"";
    contentStr += inverterTemp;
    contentStr += "\",\"acFrequency\":\"";
    contentStr += acFrequency;
    contentStr += "\"}";
    client.publish("arduino/nano33_1/monitor", contentStr.c_str(), false);
    }

void mqttAutoDiscovery(){
    contentStr = "{\"name\":\"Nano33 1 status\",\"uniq_id\":\"Nano33 EM\",\"ic\":\"mdi:gauge\",\"stat_t\":\"arduino/nano33_1/status\",\"val_tpl\":\"{{value_json['online']}}\",\"dev\":{\"name\":\"Nano33 Solis Energy Monitor\",\"sw\":\"1.1.0\",\"mf\":\"Arduino & Phil\",\"mdl\":\"Nano 33\",\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/system/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 RSSI\",\"uniq_id\":\"rssi1\",\"unit_of_meas\":\"%\",\"ic\":\"mdi:access-point\",\"stat_t\":\"arduino/nano33_1/heartbeat\",\"val_tpl\":\"{{value_json.rssi}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/rssi/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 AP\",\"uniq_id\":\"ap1\",\"unit_of_meas\":\"\",\"ic\":\"mdi:access-point\",\"stat_t\":\"arduino/nano33_1/heartbeat\",\"val_tpl\":\"{{value_json.AP}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/ap/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 uptimeDay\",\"uniq_id\":\"uptimeDay1\",\"unit_of_meas\":\"d\",\"ic\":\"mdi:clock-check-outline\",\"stat_t\":\"arduino/nano33_1/heartbeat\",\"val_tpl\":\"{{value_json.uptimeDay}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/uptimeDay/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 uptimeMin\",\"uniq_id\":\"uptimeMin1\",\"unit_of_meas\":\"m\",\"ic\":\"mdi:clock-check-outline\",\"stat_t\":\"arduino/nano33_1/heartbeat\",\"val_tpl\":\"{{value_json.uptimeMin}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/uptimeMin/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 Active Power\", \"uniq_id\":\"activePower1\", \"dev_cla\":\"power\", \"unit_of_meas\":\"W\", \"ic\":\"mdi:flash\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.activePower|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/activePower/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 Total Energy\", \"uniq_id\":\"totalEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.totalEnergy|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/totalEnergy/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 Energy this month\", \"uniq_id\":\"thismonthEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.thismonthEnergy|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/thismonthEnergy/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 Energy last month\", \"uniq_id\":\"lastmonthEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.lastmonthEnergy|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/lastmonthEnergy/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);
    
    contentStr = "{\"name\":\"Nano33 1 Energy today\", \"uniq_id\":\"todayEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.todayEnergy|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/todayEnergy/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);
    
    contentStr = "{\"name\":\"Nano33 1 Energy last day\", \"uniq_id\":\"lastdayEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.lastdayEnergy|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/lastdayEnergy/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);
    
    contentStr = "{\"name\":\"Nano33 1 Energy this year\", \"uniq_id\":\"thisyearEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.thisyearEnergy|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/thisyearEnergy/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);
    
    contentStr = "{\"name\":\"Nano33 1 Energy last year\", \"uniq_id\":\"lastyearEnergy1\", \"dev_cla\":\"energy\", \"unit_of_meas\":\"kWh\", \"ic\":\"mdi:sigma\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.lastyearEnergy|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/lastyearEnergy/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);
    
    contentStr = "{\"name\":\"Nano33 1 DC Voltage\", \"uniq_id\":\"dcVolts1\", \"dev_cla\":\"voltage\", \"unit_of_meas\":\"V\", \"ic\":\"mdi:flash-triangle-outline\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.dcVolts|round(1)}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/dcVolts/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);
    
    contentStr = "{\"name\":\"Nano33 1 DC Amps\", \"uniq_id\":\"dcAmps1\", \"dev_cla\":\"current\", \"unit_of_meas\":\"A\", \"ic\":\"mdi:current-dc\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.dcAmps|round(1)}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/dcAmps/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 Inverter Temp\", \"uniq_id\":\"inverterTemp1\", \"dev_cla\":\"temperature\", \"unit_of_meas\":\"C\", \"ic\":\"mdi:thermometer\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.inverterTemp|int}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/inverterTemp/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);

    contentStr = "{\"name\":\"Nano33 1 AC Frequency\", \"uniq_id\":\"acFrequency1\", \"dev_cla\":\"frequency\", \"unit_of_meas\":\"Hz\", \"ic\":\"mdi:sine-wave\", \"stat_t\":\"arduino/nano33_1/monitor\", \"val_tpl\":\"{{value_json.acFrequency|round(1)}}\", \"dev\":{\"ids\":[\"nano33_1\"]}}";
    topicStr = "homeassistant/sensor/nano33_1/acFrequency/config";
    client.publish(topicStr.c_str(), contentStr.c_str(), false);
    }
    
    void mqttTime(){
    contentStr = "{\"inverterYear\":\"";
    contentStr += inverterYear;
    contentStr += "\",\"inverterMonth\":\"";
    contentStr += inverterMonth;
    contentStr += "\",\"inverterDay\":\"";
    contentStr += inverterDay;
    contentStr += "\",\"inverterHours\":\"";
    contentStr += inverterHours;
    contentStr += "\",\"inverterMinutes\":\"";
    contentStr += inverterMinutes;
    contentStr += "\",\"inverterSeconds\":\"";
    contentStr += inverterSeconds;
    contentStr += "\"}";
    client.publish("arduino/nano33_1/time", contentStr.c_str(), false);
    }
  
