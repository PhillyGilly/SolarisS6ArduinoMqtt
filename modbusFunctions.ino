
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

void modbusData(){
  int wait = 100;
 
  if (millis() - lastMillis > rate) {
    lastMillis = millis();
    modbusMsg = "{";
    //make all the read calls
    delay(wait);
    activePower = readactivePower();
    delay(wait);
    totalEnergy = readtotalEnergy();
    delay(wait);
    thismonthEnergy = readthismonthEnergy();
    delay(wait);
    lastmonthEnergy = readlastmonthEnergy();
    delay(wait);
    todayEnergy = readtodayEnergy();
    delay(wait);
    lastdayEnergy = readlastdayEnergy();
    delay(wait);
    thisyearEnergy = readthisyearEnergy();
    delay(wait);
    lastyearEnergy = readlastyearEnergy();
    delay(wait);
    dcVolts = readdcVolts();
    delay(wait);
    dcAmps = readdcAmps();
    delay(wait);
    inverterTemp = readinverterTemp();
    delay(wait);
    acFrequency = readacFrequency();
    delay(wait);
    modbusMsg += "}";
    }
}

double readactivePower(){
  activePower = 0;
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3004, 2)) {
    modbusMsg += "\"activePower\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    activePower = double1;
  }
  return activePower;
}  

double readtotalEnergy(){
  totalEnergy = 0;
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3008, 2)) {
    modbusMsg += "\"totalEnergy\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    totalEnergy = double1;
  }
  return totalEnergy;
}  

double readthismonthEnergy(){
  thismonthEnergy = 0;
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3010, 2)) {
    modbusMsg += "\"thismonthEnergy\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    thismonthEnergy = double1;
  }
  return thismonthEnergy;
}

double readlastmonthEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3012, 2)) {
    modbusMsg += "\"lastmonthEnergy\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    lastmonthEnergy = double1;
  }
  return lastmonthEnergy;
}

float readtodayEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3014, 1)) {
    modbusMsg += "\"todayEnergy\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();  
    todayEnergy = word1/10;
  }
  return todayEnergy;
}

float readlastdayEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3015, 1)) { 
    modbusMsg += "\"lastdayEnergy\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();  
    lastdayEnergy = word1/10;
  }
  return lastdayEnergy;
}

double readthisyearEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3016, 2)) {
    modbusMsg += "\"thisyearEnergy\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    thisyearEnergy = double1;
  }
  return thisyearEnergy;
}

double readlastyearEnergy(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3018, 2)) {
    modbusMsg += "\"lastyearEnergy\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();
    uint16_t word2 = ModbusRTUClient.read();
    int32_t double1 = word1 << 16 | word2;
    lastyearEnergy = double1;
  }
  return thisyearEnergy;
}

float readdcVolts(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3021, 1)) { 
    modbusMsg += "\"dcVolts\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();  
    dcVolts = word1/10;
  }
  return dcVolts;
}

float readdcAmps(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3022, 1)) { 
    modbusMsg += "\"dc Amps\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();  
    dcAmps = word1/10;
  }
  return dcAmps;
}

float readinverterTemp(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3041, 1)) { 
    modbusMsg += "\"inverterTemp\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\",";
  }else{
    uint16_t word1 = ModbusRTUClient.read();  
    inverterTemp = word1/10;
  }
  return inverterTemp;
}

float readacFrequency(){
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 3042, 1)) { 
    modbusMsg += "\"acFrequency\":\"";
    modbusMsg += ModbusRTUClient.lastError();
    modbusMsg += "\"";
  }else{
    uint16_t word1 = ModbusRTUClient.read();  
    acFrequency = word1/100;
  }
  return acFrequency;
}
