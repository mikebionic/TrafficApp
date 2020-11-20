String data;
String dataPart;
long timeConserved = 0;
long timeUsing = 0;
const int redLed = 3;
const int greenLed = 4;
const int yellowLed = 5;
int redState = LOW;
int yellowState = LOW;
int greenState = LOW;
unsigned long currentTime = millis();
long startTime = 0;
long elapsedTime = currentTime - startTime;
long cycleTime = 15000;
bool updateTime = true;
void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0)
  {
    data = (Serial.readStringUntil("\n"));
    dataPart = (getValue(data, '/', 1));
    timeConserved = dataPart.toInt();
    Serial.println(timeConserved); 
    if (updateTime == true)
    {
      timeUsing = timeConserved;
      updateTime = false;
    }
  }
  Serial.println(timeUsing);
  currentTime = millis();
  elapsedTime = currentTime - startTime;
  if (elapsedTime > cycleTime)
  {
    startTime = currentTime;
    timeUsing = timeConserved;
  }
  if (elapsedTime > 10000)
  {
    redState = HIGH;
  }
  else redState = LOW;
  
  if (elapsedTime > 7000 && elapsedTime < 10000)
  {
    yellowState = HIGH;
  }
  else yellowState = LOW;
  if (elapsedTime < 7000)
  {
    greenState = HIGH;
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
