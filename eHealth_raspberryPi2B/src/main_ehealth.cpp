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

int cont = 0;   //����ѭ����ȡѪ�������ı���
void setup();    //�Դ�������ʼ��
void loop();     //��ȡ����������ֵ
void readPulsioximeter();  //�жϺ���
void *AirFlow(void* arg);  //���̼߳���������

int main (){
	printf("Wellcome to use the eHealth!\n");
	setup();
	pthread_t tid;    //���߳�id
	int ret;         //�����̷߳���ֵ
    ret = pthread_create(&tid, NULL, AirFlow, NULL);        //�������߳�
	if(ret < 0){
        printf("creat 0 thread failure\n");    //�̴߳���ʧ��
        return -1;
    }
	loop();    //�ռ�����������
    pthread_join(tid,NULL);    //�ȴ����߳���ֹ
	unistd::sleep(2);    //��˯2��
	return 0;
}

void setup(){
	eHealth.readGlucometer();     //��ʼ��Ѫ�Ǵ�����
	delay(100);     //�ӳٺ���
	eHealth.initPositionSensor();   //��ʼ������λ�ô�����
	Serial.begin(115200);          //���ò�����
	delay(100);
	eHealth.initPulsioximeter();     //��ʼ��Ѫ��������
    delay(100);
	//Attach the inttruptions for using the pulsioximeter.
	attachInterrupt(6, readPulsioximeter, RISING);    //����6�����ŵ�ƽ�仯�ж�
    delay(100);
	eHealth.readBloodPressureSensor();          //��ȡѪѹ������
	delay(100);
}


void readPulsioximeter(){    //���Ѫ�����жϺ���
	cont ++;
	if (cont == 50) {   //Get only of one 50 measures to reduce the latency
		eHealth.readPulsioximeter();
		cont = 0;
  }
}

void *AirFlow(void* arg){      //�����������߳�ִ�к���
	int avgs,sum=0;
	for(int n=0; n < 1000; n++){
		int air = eHealth.getAirFlow();
        unistd::usleep(30000);
		sum=+air;
	}
	avgs=sum/1000;
}

void loop(){      //��������������ĺ���
	float ECG = eHealth.getECG();      //�ĵ�ͼ
	
	int EMG = eHealth.getEMG();     //����ͼ
	
	float temperature = eHealth.getTemperature();   //����
	
	float conductance = eHealth.getSkinConductance();   //������
	float resistance = eHealth.getSkinResistance();    //����
	float conductanceVol = eHealth.getSkinConductanceVoltage();   //��ѹ
	
	int BPM = eHealth.getBPM();  //����
	int Oxy = eHealth.getOxygenSaturation();   //������
	digitalWrite(2,HIGH);            //����2�ø�
	
	uint8_t position = eHealth.getBodyPosition();    //��ȡ����λ��
	
	uint8_t numberOfData_gl = eHealth.getGlucometerLength();    //����Ѫ�������ݸ���
	int *day_gl = new int[numberOfData_gl];
	int *month_gl = new int[numberOfData_gl];
	int *year_gl = new int[numberOfData_gl];
	int *hour_gl = new int[numberOfData_gl];
	int *minutes_gl = new int[numberOfData_gl];
	int *glucose = new int[numberOfData_gl];             
	for (int i = 0; i<numberOfData_gl; i++) {            //�������в���ֵ�Լ���Ӧ��ʱ��
		day_gl[i] = eHealth.glucoseDataVector[i].day;    
		month_gl[i] = eHealth.glucoseDataVector[i].month;
		year_gl[i] = eHealth.glucoseDataVector[i].year;
		hour_gl[i] = eHealth.glucoseDataVector[i].hour;
		minutes_gl[i] = eHealth.glucoseDataVector[i].minutes;
		glucose[i] = eHealth.glucoseDataVector[i].glucose;
    }
	
	uint8_t numberOfData_bl = eHealth.getBloodPressureLength();         //����Ѫѹ�����ݸ���
	int *day_bl = new int[numberOfData_bl];
	int *month_bl = new int[numberOfData_bl];
	int *year_bl = new int[numberOfData_bl];
	int *hour_bl = new int[numberOfData_bl];
	int *minutes_bl = new int[numberOfData_bl];
	int *systolic = new int[numberOfData_bl];
	int *diastolic = new int[numberOfData_bl];
	int *pulse = new int[numberOfData_bl];
	for (int i = 0; i<numberOfData_bl; i++) {                        //�������������Լ���Ӧ��ʱ��
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


