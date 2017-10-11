#make the ehealth project

#bin/main_ehealth-app:src/main_ehealth.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/main_ehealth-app -Iinclude src/main_ehealth.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

bin/main_ehealth_old-app:src/main_ehealth_old.cpp obj/arduPi.o obj/eHealth.o
	g++ -o bin/main_ehealth_old-app -Iinclude src/main_ehealth_old.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/airflow-app:src/examples/airflow.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/airflow-app -Iinclude src/examples/airflow.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/bloodpressure-app:src/examples/bloodpressure.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/bloodpressure-app -Iinclude src/examples/bloodpressure.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/ecg-app:src/examples/ecg.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/ecg-app -Iinclude src/examples/ecg.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/emg-app:src/examples/emg.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/emg-app -Iinclude src/examples/emg.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/galvanic-app:src/examples/galvanic.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/galvanic-app -Iinclude src/examples/galvanic.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/positionometer-app:src/examples/positionometer.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/positionometer-app -Iinclude src/examples/positionometer.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/pulsioximeter-app:src/examples/pulsioximeter.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/pulsioximeter-app -Iinclude src/examples/pulsioximeter.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/temperature-app:src/examples/temperature.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/temperature-app -Iinclude src/examples/temperature.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

#bin/glucometer-app:src/examples/glucometer.cpp obj/arduPi.o obj/eHealth.o
#	g++ -o bin/glucometer-app -Iinclude src/examples/glucometer.cpp obj/arduPi.o obj/eHealth.o -lpthread -lrt

obj/arduPi.o:src/arduPi.cpp
	g++ -o obj/arduPi.o -Iinclude -c src/arduPi.cpp

obj/eHealth.o:src/eHealth.cpp
	g++ -o obj/eHealth.o -Iinclude -c src/eHealth.cpp

