# SolarisS6ArduinoMqtt

##Background
Project to get data from my Solaris S6 inverter into Home Assistant by MQTT.
This avoids the cost of buying a dongle and any delays/security issues with using the cloud based apps.
Thanks to RichardL64 https://github.com/RichardL64/Solar for seeding the idea.



##Hardware:
Arduino Nano33 IOT (plus USB power supply)
Puretek XY-017 RS485 TO TTL Breakout For Arduino buy here https://www.ebay.co.uk/itm/274273632839
(note: the silkscreen for the RS485 cables is marked back to front - so if it doesn’t work - swap the cables).
Exceedconn EC04681-2023-BF Male/Female for Solis/Ginlong Inverter RS-485 port buy here https://www.ebay.co.uk/itm/195464332269

##Please note:
a) The code is fairly simple and undocumented.
b) The arduino just posts out the modbus data by mqtt as soon as it reads it, so there isn't any need to hold it locally. It's just keep it in global variables.
c) The functions are crude and do contain some duplications. Configuration for things like modbus and mqtt is hard coded into the functions.
d) As the purpose is to get data into Home Assistant there is quite a lot of mqtt associated with device/entity auto-discovery.
e) The inverter powers down completely when the sun isn't shining (option in the Advanced settings: 24H Switch Disabled) to avoind powring the interter at ~60W overningt.
To avoid the risk of corrupted values arriving in HA, the code tests to see if the modbus has stopped communicating to detect inverter powered down.
When that is detected "dynamic" values are set to 0 and "integrated" values are set to their last known value.
f) The passowrd for OTA is hard  coded. All other passwords etc. need setting in arduino-secrets.h 

Future work:
g) Synchronise the inverter time with the Arduino (and HA). The code reads the time from the Solaris and writes it in json so it can be read.
But I haven't worked out how to get the time data in the Arduino and format it to be written into the modbus.
h) Data resolution. Active Power only reports to the nearest 20W.
This seems weird for an unsigned short (i.e. 0 to 65,535) and an 3.6kW inverter (i.e. 0 to 3,600).  I would have expected to see reporting to the nearest 0.1W.

Any ideas on the above welcomed

Cheers and thank you!


