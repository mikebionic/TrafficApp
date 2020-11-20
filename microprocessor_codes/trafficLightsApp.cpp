long trafficLight1Time = millis();
bool updateTraffic1Time = true;
long traffic1Delay = 0;
long traffic1DelayConserved = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() != 0){
    String data = Serial.readStringUntil("\n");
    data.trim();
    Serial.println("catched data from serial " + data);
    traffic1DelayConserved = data.toInt();
  }
  if (updateTraffic1Time == true){
    traffic1Delay = traffic1DelayConserved;
  }
  controlTraffic();
}

void controlTraffic(){
  
  if(trafficLight1Time + traffic1Delay > millis()){
    updateTraffic1Time = false;
    Serial.println("light is on " + String(traffic1Delay));
    updateTraffic1Time = true;
  }
}
