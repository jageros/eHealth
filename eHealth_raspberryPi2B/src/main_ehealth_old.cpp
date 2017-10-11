#include "eHealth.h"

int cont = 0;
void setup();
void loop();
void readPulsioximeter();
void *AirFlow(void* arg);

int main (){
	setup();
	pthread_t tid;
	int ret;
    ret = pthread_create(&tid, NULL, AirFlow, NULL);
	if(ret < 0){
        printf("creat 0 thread failure\n");
        return -1;
    }
    while(1){
	    loop();
        unistd::sleep(2);
    }
    pthread_join(tid,NULL);
	return 0;
}

void setup(){
	eHealth.readGlucometer();
	delay(100);
//	eHealth.initPositionSensor();
	Serial.begin(115200);
	delay(100);
	eHealth.initPulsioximeter();
    delay(100);
	//Attach the inttruptions for using the pulsioximeter.
	attachInterrupt(6, readPulsioximeter, RISING);
    delay(100);
}


void readPulsioximeter(){
	cont ++;
	if (cont == 500) {   //Get only of one 50 measures to reduce the latency
		eHealth.readPulsioximeter();
		cont = 0;
  }
}

void *AirFlow(void* arg){
	while(1){
		int air = eHealth.getAirFlow();
		printf("air:%d\n", air/5);
		delay(3000);
        unistd::usleep(30000);
	}
}

void loop(){
	float ECG = eHealth.getECG();
	printf("ECG:%f\n", ECG);
	delay(2000);
	float temperature = eHealth.getTemperature();
	printf("temperature:%f\n", temperature);
	delay(3000);
	float conductance = eHealth.getSkinConductance();
	float resistance = eHealth.getSkinResistance();
	float conductanceVol = eHealth.getSkinConductanceVoltage();
	printf("Skin:\nConductance:%f\tResistance:%f\tVoltage:%f\n", conductance, resistance, conductanceVol);
    delay(2000);
	int BPM = eHealth.getBPM();
	int Oxy = eHealth.getOxygenSaturation();
	printf("BPM:%d\tOxy:%d\n", BPM, Oxy);
	delay(2000);
	digitalWrite(2,HIGH);
//	uint8_t position = eHealth.getBodyPosition();
//	printf("position:%d", position);
	delay(3000);
	uint8_t numberOfData = eHealth.getGlucometerLength();
	int *day = new int[numberOfData];
	int *month = new int[numberOfData];
	int *year = new int[numberOfData];
	int *hour = new int[numberOfData];
	int *minutes = new int[numberOfData];
	int *glucose = new int[numberOfData];
	for (int i = 0; i<numberOfData; i++) {
		day[i] = eHealth.glucoseDataVector[i].day;
		month[i] = (int)eHealth.numberToMonth(eHealth.glucoseDataVector[i].month);
		year[i] = eHealth.glucoseDataVector[i].year;
		hour[i] = eHealth.glucoseDataVector[i].hour;
		minutes[i] = eHealth.glucoseDataVector[i].minutes;
		glucose[i] = eHealth.glucoseDataVector[i].glucose;
		printf("%d-%s-%d %d:%d :Glucose value : %d mg/dL\n", year[i]+2000, month[i], day[i], hour[i], minutes[i], glucose[i]);
		delay(2000);
    }
}


