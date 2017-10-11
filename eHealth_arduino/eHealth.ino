/*
 *  eHealth sensor platform for Arduino and Raspberry from Cooking-hacks.
 *
 *  Description: "The e-Health Sensor Shield allows Arduino and Raspberry Pi 
 *  users to perform biometric and medical applications by using 9 different 
 *  sensors: Pulse and Oxygen in Blood Sensor (SPO2), Airflow Sensor (Breathing),
 *  Body Temperature, Electrocardiogram Sensor (ECG), Glucometer, Galvanic Skin
 *  Response Sensor (GSR - Sweating), Blood Pressure (Sphygmomanometer) and 
 *  Patient Position (Accelerometer)."  
 *
 *  Explanation: This example shows the way to communicate with  
 *  the Arduino Wifi Demo Android app. 
 *
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version 2.0
 *  Author: Luis Martin & Ahmad Saad 
 */
 
 
#include <PinChangeInt.h>
#include <eHealth.h>

char recv[128];
uint8_t cont = 0;

void readPulsioximeter();

void setup()
{ 
  Serial.begin(115200);
  
  eHealth.initPulsioximeter();
  eHealth.initPositionSensor(); 
   
  
  //Attach the inttruptions for using the pulsioximeter.   
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  delay(1000);
  
}

void loop()
{
    while(1){     
      //1. Read from eHealth. 
       int airFlow = eHealth.getAirFlow();     //呼吸
       float temperature = eHealth.getTemperature();     //体温
       float conductance = eHealth.getSkinConductance();  //导电率 
       float resistance = eHealth.getSkinResistance();    //电阻
       //float conductanceVol = eHealth.getSkinConductanceVoltage();  //导电率的电压
       int BPM = eHealth.getBPM();         //脉搏
       int SPO2 = eHealth.getOxygenSaturation();     //血氧饱和度
       //uint8_t pos = eHealth.getBodyPosition();      //身体位置
       //int syst = eHealth.getSystolicPressure(1);   //收缩压
       //int diast = eHealth.getDiastolicPressure(1);     //舒张压
      // float ECG = eHealth.getECG();     //心电图
       //uint8_t glucose = eHealth.glucoseDataVector[0].glucose;     //血糖 
      //Data sensor must be sent in this order to mobile android application 
    
      Serial.print(int(airFlow));     Serial.print("#");
      Serial.print(int(temperature)); Serial.print("#");
      Serial.print(int(BPM));         Serial.print("#")；
      Serial.print(int(SPO2));        Serial.print("#");
      Serial.print("\n");    
    
      // Reduce this delay for more data rate
      delay(250);  
  }
}

void readPulsioximeter(){  
  
  cont ++;
 
  if (cont == 50) { //Get only one of 50 measures to reduce the latency
    eHealth.readPulsioximeter();  
    cont = 0;
  }
}

