/*
 *	eHealth Program
 *
 *  eHealth sensor platform for Arduino and Raspberry from Cooking-hacks.
 *
 *  Description: "The e-Health Sensor Shield allows Arduino and Raspberry Pi 
 *  users to perform biometric and medical applications by using 9 different 
 *  sensors: Pulse and Oxygen in Blood Sensor (SPO2), Airflow Sensor (Breathing),
 *  Body Temperature, Electrocardiogram Sensor (ECG), Glucometer, Galvanic Skin
 *  Response Sensor (GSR - Sweating), Blood Pressure (Sphygmomanometer) and 
 *  Patient Position (Accelerometer)."
 *
 *	Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *	Version 2.4
 *  Author: lhj & hjx
 */


#include "eHealth.h"

int cont = 0;   //用于循环读取血氧次数的变量
void setup();    //对传感器初始化
void loop();     //读取传各感器数值
void readPulsioximeter();  //中断函数
void *AirFlow(void* arg);  //子线程检测呼吸函数

int main (){
	printf("Wellcome to use the eHealth!\n");
	setup();
	pthread_t tid;    //子线程id
	int ret;         //创建线程返回值
    ret = pthread_create(&tid, NULL, AirFlow, NULL);        //创建子线程
	if(ret < 0){
        printf("creat 0 thread failure\n");    //线程创建失败
        return -1;
    }
	loop();    //收集传感器数据
    pthread_join(tid,NULL);    //等待子线程终止
	unistd::sleep(2);    //沉睡2秒
	return 0;
}

void setup(){
	eHealth.readGlucometer();     //初始化血糖传感器
	delay(100);     //延迟函数
	eHealth.initPositionSensor();   //初始化身体位置传感器
	Serial.begin(115200);          //设置波特率
	delay(100);
	eHealth.initPulsioximeter();     //初始化血氧传感器
    delay(100);
	//Attach the inttruptions for using the pulsioximeter.
	attachInterrupt(6, readPulsioximeter, RISING);    //设置6号引脚电平变化中断
    delay(100);
	eHealth.readBloodPressureSensor();          //读取血压传感器
	delay(100);
}


void readPulsioximeter(){    //检测血氧的中断函数
	cont ++;
	if (cont == 50) {   //Get only of one 50 measures to reduce the latency
		eHealth.readPulsioximeter();
		cont = 0;
  }
}

void *AirFlow(void* arg){      //检测呼吸的子线程执行函数
	int avgs,sum=0;
	for(int n=0; n < 1000; n++){
		int air = eHealth.getAirFlow();
        unistd::usleep(30000);
		sum=+air;
	}
	avgs=sum/1000;
}

void loop(){      //检测其他传感器的函数
	float ECG = eHealth.getECG();      //心电图
	
	int EMG = eHealth.getEMG();     //肌电图
	
	float temperature = eHealth.getTemperature();   //体温
	
	float conductance = eHealth.getSkinConductance();   //导电率
	float resistance = eHealth.getSkinResistance();    //电阻
	float conductanceVol = eHealth.getSkinConductanceVoltage();   //电压
	
	int BPM = eHealth.getBPM();  //心率
	int Oxy = eHealth.getOxygenSaturation();   //含氧量
	digitalWrite(2,HIGH);            //引脚2置高
	
	uint8_t position = eHealth.getBodyPosition();    //读取身体位置
	
	uint8_t numberOfData_gl = eHealth.getGlucometerLength();    //返回血糖仪数据个数
	int *day_gl = new int[numberOfData_gl];
	int *month_gl = new int[numberOfData_gl];
	int *year_gl = new int[numberOfData_gl];
	int *hour_gl = new int[numberOfData_gl];
	int *minutes_gl = new int[numberOfData_gl];
	int *glucose = new int[numberOfData_gl];             
	for (int i = 0; i<numberOfData_gl; i++) {            //返回所有测量值以及对应的时间
		day_gl[i] = eHealth.glucoseDataVector[i].day;    
		month_gl[i] = eHealth.glucoseDataVector[i].month;
		year_gl[i] = eHealth.glucoseDataVector[i].year;
		hour_gl[i] = eHealth.glucoseDataVector[i].hour;
		minutes_gl[i] = eHealth.glucoseDataVector[i].minutes;
		glucose[i] = eHealth.glucoseDataVector[i].glucose;
    }
	
	uint8_t numberOfData_bl = eHealth.getBloodPressureLength();         //返回血压计数据个数
	int *day_bl = new int[numberOfData_bl];
	int *month_bl = new int[numberOfData_bl];
	int *year_bl = new int[numberOfData_bl];
	int *hour_bl = new int[numberOfData_bl];
	int *minutes_bl = new int[numberOfData_bl];
	int *systolic = new int[numberOfData_bl];
	int *diastolic = new int[numberOfData_bl];
	int *pulse = new int[numberOfData_bl];
	for (int i = 0; i<numberOfData_bl; i++) {                        //返回所有数据以及对应的时间
		day_bl[i] = eHealth.bloodPressureDataVector[i].day;
		month_bl[i] = eHealth.bloodPressureDataVector[i].month;
		year_bl[i] = 2000 + eHealth.bloodPressureDataVector[i].year;
		hour_bl[i] = eHealth.bloodPressureDataVector[i].hour;
		minutes_bl[i] = eHealth.bloodPressureDataVector[i].minutes;
		systolic[i] = 30+eHealth.bloodPressureDataVector[i].systolic;
		diastolic[i] = eHealth.bloodPressureDataVector[i].diastolic;
 		pulse[i] = eHealth.bloodPressureDataVector[i].pulse;
		
	}
	
}


