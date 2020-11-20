String data;
const int redLed = 3;
const int greenLed = 4;
const int yellowLed = 5;
int redState = LOW;
int yellowState = LOW;
int greenState = LOW;
unsigned long currentTime = millis();
long startTime = 0;
long elapsedTime = currentTime - startTime;
long cycleTime = 30000;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  elapsedTime = currentTime - startTime;
  if (elapsedTime > cycleTime)
  {
    startTime = currentTime;
  }
  Serial.println("Start");
  if (elapsedTime > 20000)
  {
    redState = HIGH;
    Serial.println("Red");
  }
  else redState = LOW;
  
  if (elapsedTime > 15000 && elapsedTime < 20000)
  {
    yellowState = HIGH;
    Serial.println("Yellow");
  }
  else yellowState = LOW;
  if (elapsedTime < 15000)
  {
    greenState = HIGH;
    Serial.println("Green");
  }
  else greenState = LOW;

  digitalWrite(redLed, redState);
  digitalWrite(yellowLed, redState);
  digitalWrite(greenLed, redState);
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
