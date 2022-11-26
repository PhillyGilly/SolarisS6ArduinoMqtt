// 24/11/22 10:00
// version 4.0
// working for modbus
// includes read time
// use ArduinoMQTT
// future.  write time
// use structures/arrays??

#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>
#include <NTPClient.h>
#include <ArduinoModbus.h>
#include <ArduinoRS485.h>
#include <ArduinoOTA.h>
#include "arduino_secrets.h"

char  wifi_ssid[] = SECRET_SSID;
char  wifi_pass[]  = SECRET_PASS;
char  mqtt_server[] = SECRET_MQTT_SERVER;
char  mqtt_user[] = SECRET_MQTT_USER;
char  mqtt_pass[] = SECRET_MQTT_PASS;

//For mqtt
String topicStr;
String contentStr;
//For EM
double activePower;
double totalEnergy;
double thismonthEnergy;
double lastmonthEnergy;
float todayEnergy;
float lastdayEnergy;
double thisyearEnergy;
double lastyearEnergy;
float dcVolts;
float dcAmps;
float inverterTemp;
float acFrequency;
//For Time
float inverterYear;
float inverterMonth;
float inverterDay;
float inverterHours;
float inverterMinutes;
float inverterSeconds;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
//MqttClient mqttClient(256);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup() {
//  Serial.begin(9600);
// set up wifi
  while (WiFi.begin(wifi_ssid, wifi_pass)!= WL_CONNECTED) {delay(1000);}
 
// set up MQTT  
  mqttClient.setId("nano33_1");
  mqttClient.setUsernamePassword(mqtt_user, mqtt_pass);
  while (!mqttClient.connect(mqtt_server, 1883)) {delay(1000);}
  
// set up OTA
  ArduinoOTA.begin(WiFi.localIP(),"nano33-1","nano1pass", InternalStorage);

// set up Modbus
  ModbusRTUClient.begin(9600);
  
  timeClient.begin();
}

void loop() {
// check connection to MQTT server
  while (!mqttClient.connect(mqtt_server, 1883))
  {
    WiFi.begin(wifi_ssid, wifi_pass);
    delay(1000);
  }
  
  mqttClient.poll();
  ArduinoOTA.poll();
  mqttAutoDiscovery();
  mqttHeartbeat();
  mqttStatus();
  mqttData();
  mqttTime();
  delay(8800);
}

