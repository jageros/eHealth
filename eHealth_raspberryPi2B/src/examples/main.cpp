#include"../include/eHealth.h"

int cont = 0;
void setup();
void loop();
void readPulsioximeter();
void sendBloodPressureData();

int main (){
	setup();
	while(1){
		loop();
	}
	return (0);
}

void setup(){
	eHealth.readGlucometer();
	delay(100);
	eHealth.initPositionSensor();
	Serial.begin(115200);
	delay(100);
	eHealth.initPulsioximeter();
	//Attach the inttruptions for using the pulsioximeter.
	attachInterrupt(6, readPulsioximeter, RISING);
}

void loop(){
	int air = eHealth.getAirFlow();
	printf("1--air:%d\n", air);
	uint8_t position = eHealth.getBodyPosition();
	printf("7--position:%d", position);
	float ECG = eHealth.getECG();
	printf("2--ECG:%f\n", ECG);
	//int EMG = eHealth.getEMG();
	//printf("3--EMG:%d\n", EMG);
	uint8_t numberOfData = eHealth.getGlucometerLength();
	int BPM = eHealth.getBPM();
	int Oxy = eHealth.getOxygenSaturation();
	printf("6--BPM:%d\tOxy:%d\n", BPM, Oxy);
	digitalWrite(2,HIGH);
	float conductance = eHealth.getSkinConductance();
    float resistance = eHealth.getSkinResistance();
    float conductanceVol = eHealth.getSkinConductanceVoltage();
	printf("5--Skin:\nConductance:%f\tResistance:%f\tVoltage:%f\n", conductance, resistance, conductanceVol);
	float temperature = eHealth.getTemperature();
	printf("4--temperature:%f", temperature);
	sendBloodPressureData();
}

void readPulsioximeter(){
	cont ++;
	if (cont == 500) { //Get only of one 50 measures to reduce the latency
		eHealth.readPulsioximeter();
		cont = 0;
  }
}

void sendBloodPressureData(){
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
		year[i] = 2000 + eHealth.glucoseDataVector[i].year;
		hour[i] = eHealth.glucoseDataVector[i].hour;
		minutes[i] = eHealth.glucoseDataVector[i].minutes;
		glucose[i] = eHealth.glucoseDataVector[i].glucose;
		printf("%d-%s-%d %d:%d :Glucose value : %d mg/dL", year[i]+2000, month[i], day[i], hour[i], minutes[i], glucose[i]);
    }
}
