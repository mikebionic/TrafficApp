String data;
String dataPart1;
String dataPart2;

long timeConserved1 = 0;
long timeUsing1 = 0;
long timeConserved2 = 0;
long timeUsing2 = 0;

const int redLed = 5;
const int greenLed = 6;
const int yellowLed = 7;
const int yellowLed1 = 8;

int yellowState1 = LOW;
int redState = LOW;
int yellowState = LOW;
int greenState = LOW;

unsigned long currentTime = millis();

long startTime = 0;
long elapsedTime = currentTime - startTime;
long cycleTime = 23000;

unsigned long greenTimeGreater;
unsigned long greenTimeLess;

bool updateTime = true;
bool stringComplete = false;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed1, OUTPUT);
  Serial.begin(9600);
  data.reserve(200);
}

void loop() {
  if(stringComplete)
  {
    // example: road1/12/road2/19
    dataPart1 = getValue(data, '/', 1);
    dataPart2 = getValue(data, '/', 3);
    timeConserved1 = dataPart1.toInt();
    timeConserved2 = dataPart2.toInt();
    if(updateTime == true)
    {
      timeUsing1 = timeConserved1;
      timeUsing2 = timeConserved2;
      updateTime = false;
    }
    data = "";
    stringComplete = false;
  }
  Serial.println(timeUsing1);
  Serial.println(timeUsing2);
  digitalWrite(redLed, redState);
  digitalWrite(yellowLed, yellowState);
  digitalWrite(greenLed, greenState);
  digitalWrite(yellowLed1,yellowState1);
  greenTimeGreater = timeUsing1 * 800;
  greenTimeLess = timeUsing2 * 800;
  currentTime = millis();
  elapsedTime = currentTime - startTime;
  if(timeUsing1 >= timeUsing2)
  {
    if(timeUsing1 <= 20)
    {
      if(elapsedTime < 3000)
      {
      yellowState1 = HIGH;
      }
      else yellowState1 = LOW;

      if (elapsedTime > 3000 && elapsedTime < 10000)
      {
      greenState = HIGH;
      }
      else greenState = LOW;
    
      if (elapsedTime > 10000 && elapsedTime < 13000)
      {
      yellowState = HIGH;
      }
      else yellowState = LOW;
    
      if (elapsedTime > 13000)
      {
      redState = HIGH;
      }
      else redState = LOW;

      if (elapsedTime > cycleTime)
      {
      startTime = currentTime;
      timeUsing1 = timeConserved1;
      timeUsing2 = timeConserved2;
      }
    }
    else
    {
      if (elapsedTime < 3000)
      {
      yellowState1 = HIGH;
      }
      else yellowState1 = LOW;

      if (elapsedTime > 3000 && elapsedTime < (greenTimeGreater + 3000))
      {
      greenState = HIGH;
      }
      else greenState = LOW;
    
      if (elapsedTime > (greenTimeGreater + 3000) && elapsedTime < (greenTimeGreater + 6000))
      {
      yellowState = HIGH;
      }
      else yellowState = LOW;
    
      if (elapsedTime > (greenTimeGreater + 6000))
      {
      redState = HIGH;
      }
      else redState = LOW;
      
      if (elapsedTime > (greenTimeGreater + 16000))
      {
        startTime = currentTime;
        timeUsing1 = timeConserved1;
        timeUsing2 = timeConserved2;
      }
    }
  }
  else
  {
    if(timeUsing2 <= 20)
    {
      if (elapsedTime < 3000)
      {
      yellowState1 = HIGH;
      }
      else yellowState1 = LOW;

      if (elapsedTime > 3000 && elapsedTime < 10000)
      {
      redState = HIGH;
      }
      else redState = LOW;
    
      if (elapsedTime > 10000 && elapsedTime < 13000)
      {
      yellowState = HIGH;
      }
      else yellowState = LOW;
    
      if (elapsedTime > 13000)
      {
      greenState = HIGH;
      }
      else greenState = LOW;
      
      if (elapsedTime > cycleTime)
      {
      startTime = currentTime;
      timeUsing1 = timeConserved1;
      timeUsing2 = timeConserved2;
      }
    }
    else
    {
      if (elapsedTime < 3000)
      {
      yellowState1 = HIGH;
      }
      else yellowState1 = LOW;

      if (elapsedTime > 3000 && elapsedTime < (greenTimeLess + 3000))
      {
      redState = HIGH;
      }
      else redState = LOW;
    
      if (elapsedTime > (greenTimeLess + 3000) && elapsedTime < (greenTimeLess + 6000))
      {
      yellowState = HIGH;
      }
      else yellowState = LOW;
    
      if (elapsedTime > (greenTimeLess + 6000))
      {
      greenState = HIGH;
      }
      else greenState = LOW;

      if (elapsedTime > (greenTimeLess + 16000))
      {
        startTime = currentTime;
        timeUsing1 = timeConserved1;
        timeUsing2 = timeConserved2;
      }
    }
  }
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

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the data:
    data += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
