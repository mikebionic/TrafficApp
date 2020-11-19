long traffic_lights_time = millis();
bool updateTime = true;
long timeConserved = 0;
long timeUsing = 0;


void setup(){
	Serial.begin(9600);
}

void loop(){
	if (Serial.available() != 0){
		data = Serial.readStringUntil("\n");
		data.trim();
		if (data.length() > 0){
			timeConserved = data.toInt();
		}
	}

	if (updateTime == true){
		timeUsing = timeConserved;
	}
}

void controlTraffic(){
	if(traffic_lights_time + timeUsing > millis()){
		updateTime = false;
		Serial.println("Action traffic " + String(traffic_lights_time) + " " + String(timeUsing) );
	}
	else{
		delay(2000);
		traffic_lights_time = millis();
	}
	updateTime = true;
}