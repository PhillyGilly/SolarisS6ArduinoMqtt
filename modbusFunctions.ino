// Address    Name             Data type Unit  divisor
//3005-3006   activePower      U32       1W      1 
//3009- 3010  totalEnergy      U32       1kWh    1 
//3011- 3012  thismonthEnergy  U32       1kWh    1 
//3013- 3014  lastmonthenergy  U32       1kWh    1
//3015        todayEnergy      U16       0.1kWh  10
//3016        lastdayEnergy    U16       0.1kWh  10
//3017- 3018  thisyearEnergy   U32       1kWh    1
//3019- 3020  lastyearEnergy   U32       1kWh    1
//3022        dcVoltage        U16       0.1V    10
//3023        dcAmps           U16       0.1A    10
//3042        inverterTemp     U16       0.1C    10
//3043        acFrequency      U16       0.01Hz  100

String modbusData(){
  int wait = 100;
  unsigned long rate = 10000; // default refresh rate in ms was 60000
  unsigned long lastMillis = 0;
 
  contentStr = "{\"actP\":\"";
  contentStr += readactivePower();
  delay(wait);
  contentStr += "\",\"totE\":\"";
  contentStr += readtotalEnergy();
  delay(wait);
  contentStr += "\",\"tmthE\":\"";
  contentStr += readthismonthEnergy();
  delay(wait);
  contentStr += "\",\"lmthE\":\"";
  contentStr += readlastmonthEnergy();
  delay(wait);
  contentStr += "\",\"tdyE\":\"";
  contentStr += readtodayEnergy();
  delay(wait);
  contentStr += "\",\"ldyE\":\"";
  contentStr += readlastdayEnergy();
  delay(wait);
  contentStr += "\",\"tyE\":\"";
  contentStr += readthisyearEnergy();
  delay(wait);
  contentStr += "\",\"lyE\":\"";
  contentStr += readlastyearEnergy();
  delay(wait);
  contentStr += "\",\"dcV\":\"";
  contentStr += readdcVolts();
  delay(wait);
  contentStr += "\",\"dcA\":\"";
  contentStr += readdcAmps();
  delay(wait);
  contentStr += "\",\"invT\":\"";
  contentStr += readinverterTemp();
  delay(wait);
  contentStr += "\",\"acHz\":\"";
  contentStr += readacFrequency();
  delay(wait);
  contentStr += "\"}";
  return contentStr;
}

double readactivePower(){
  if(!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3004, 2))
  {
    activePower = 0;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    activePower = double1;
    return activePower;
  }
}  

double readtotalEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3008, 2))
  {
    totalEnergy = totalEnergy;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    totalEnergy = double1;
  }
  return totalEnergy;
}  

double readthismonthEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3010, 2))
  {
    thismonthEnergy = thismonthEnergy;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    thismonthEnergy = double1;
  }
  return thismonthEnergy;
}

double readlastmonthEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3012, 2))
  {
    lastmonthEnergy=lastmonthEnergy;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    lastmonthEnergy = double1;
  }
  return lastmonthEnergy;
}

float readtodayEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3014, 1))
  {
    todayEnergy=todayEnergy;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();  
    todayEnergy = word1/10;
  }
  return todayEnergy;
}

float readlastdayEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3015, 1))
  {
    lastdayEnergy = lastdayEnergy;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();  
    lastdayEnergy = word1/10;
  }
  return lastdayEnergy;
}

double readthisyearEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3016, 2))
  {
    thisyearEnergy = thisyearEnergy;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    thisyearEnergy = double1;
  }
  return thisyearEnergy;
}

double readlastyearEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3018, 2))
  {
    lastyearEnergy = lastyearEnergy;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    lastyearEnergy = double1;
  }
  return lastyearEnergy;
}

float readdcVolts(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3021, 1))
  {
    dcVolts = 0;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();  
    dcVolts = word1/10;
  }
  return dcVolts;
}

float readdcAmps(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3022, 1))
  {
    dcAmps = 0;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();  
    dcAmps = word1/10;
  }
  return dcAmps;
}

float readinverterTemp(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3041, 1))
  {
    inverterTemp = inverterTemp;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();  
    inverterTemp = word1/10;
  }
  return inverterTemp;
}

float readacFrequency(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3042, 1))
  {
    acFrequency = acFrequency;
  }
  else
  {
    uint16_t word1 = ModbusRTUClient.read();  
    acFrequency = word1/100;
  }
  return acFrequency;
}

// Address    Name             Data type
//3000        Year             U16       
//3001        Month            U16 
//3002        Day              U16 
//3003        Hours            U16 
//3004        Minutes          U16 
//3005        Seconds          U16 
String modbusTime(){
  String contentStr;
  if (!ModbusRTUClient.requestFrom(1, HOLDING_REGISTERS, 2999, 6))
  { 
    contentStr += "\"Time Error\":\"";
    contentStr += ModbusRTUClient.lastError();
    contentStr += "\"";
  }
  else
  {
    contentStr = "{\"invYr\":\"";
    uint16_t word1 = ModbusRTUClient.read();  
    contentStr += word1;
    contentStr += "\",\"invMth\":\"";
    uint16_t word2 = ModbusRTUClient.read();  
    contentStr += word2;
    contentStr += "\",\"invDay\":\"";
    uint16_t word3 = ModbusRTUClient.read();  
    contentStr += word3;
    contentStr += "\",\"invHr\":\"";
    uint16_t word4 = ModbusRTUClient.read();  
    contentStr += word4;
    contentStr += "\",\"invMin\":\"";
    uint16_t word5 = ModbusRTUClient.read();  
    contentStr += word5;
    contentStr += "\",\"invSec\":\"";
    uint16_t word6 = ModbusRTUClient.read();  
    contentStr += word6;
    contentStr += "\"}";
  }
  return contentStr;
