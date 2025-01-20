# SolarisS6ArduinoMqtt

## Summary
Project to get data from my Solaris S6 inverter into Home Assistant by MQTT.

This avoids the cost of buying a dongle and any delays/security issues with using the cloud based apps.

Thanks to RichardL64 https://github.com/RichardL64/Solar for seeding the idea.

## Background
I had a project to install Solar PV, a GivEnergy Hybrid Inverter, and GivEnergy batteries scheduled for completion in September 2022.

The panels were installed and the batteries delivered but the hybrid inverter was delayed repeatedly, so I decided to install a "cheap" £300 Solaris S6 inverter with the aim of learning how my panels perform so that I can develop operating strategies before the GivEnergy installation is complete.

This would require collection of data into Home Assistant to compare with consumption patterns and solar generation forecasts.

The S6 didn't come with a dongle, so I decided to make my own, this avoids the £75 cost of buying one and any delays/security issues with using the cloud based apps.
Here is the inverter with the finished arduino dongle installed in my loft.

![installed_arduino_dongle.jpg](https://github.com/PhillyGilly/SolarisS6ArduinoMqtt/blob/main/installed_arduino_dongle.jpg)

## Hardware:
The hardware used for this project:
- Arduino Nano33 IOT (plus USB power supply)
- Puretek XY-017 RS485 TO TTL Breakout For Arduino buy here https://www.ebay.co.uk/itm/274273632839
  (note: the silkscreen for the RS485 cables is marked back to front - so if it doesn’t work - swap the cables).
- Exceedconn EC04681-2023-BF Male/Female for Solis/Ginlong Inverter RS-485 port buy here www.ebay.co.uk/itm/195668989940
- Breadboard, jumpers and enclosure

Here is my Fritzing sketch of the set up.

![fritzing.png](https://github.com/PhillyGilly/SolarisS6ArduinoMqtt/blob/main/fritzing.png)

## Please note:
1. The code is fairly simple and undocumented. All my bad habits are self-taught!
2. The arduino just posts out the modbus data by mqtt as soon as it reads it, so there isn't any need to hold it locally. It's just keep it in global variables.
3. The functions are crude and do contain some duplications. Configuration for things like modbus and mqtt is hard coded into the functions.
4. As the purpose is to get data into Home Assistant there is quite a lot of mqtt associated with device/entity auto-discovery. This is what it looks like in HA:

![image](https://user-images.githubusercontent.com/56273663/204502516-35139f37-e696-4d61-b7f6-f2f6f8d1e17e.png)

5. The inverter powers down completely when the sun isn't shining (option in the Advanced settings: 24H Switch Disabled) to avoind powering the interter at ~60W overnight. To avoid the risk of corrupted values arriving in HA, the code tests to see if the modbus has stopped communicating to detect inverter powered down.
When that is detected "dynamic" values are set to 0 and "integrated" values are set to their last known value.
6. The password for OTA is hard  coded. All other passwords etc. need setting in arduino-secrets.h 

## Future work:
7. Synchronise the inverter time with the Arduino (and HA). The code reads the time from the Solaris and writes it in json so it can be read.
But I haven't worked out how to get the time data in the Arduino and format it to be written into the modbus.
8. Data resolution. Active Power only reports to the nearest 20W.
This seems weird for an unsigned short (i.e. 0 to 65,535) and an 3.6kW inverter (i.e. 0 to 3,600).  I would have expected to see reporting to the nearest 0.1W.

Any ideas on the above welcomed

Cheers and thank you!


