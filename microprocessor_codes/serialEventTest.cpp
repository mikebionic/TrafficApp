String data;
String dataPart1;
String dataPart2;

long timeConserved1 = 0;
long timeUsing1 = 0;
long timeConserved2 = 0;
long timeUsing2 = 0;

const int redLed = 13;
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
      digitalWrite(redLed,0);
  Serial.begin(9600);
  data.reserve(200);
}

void loop() {
  if(stringComplete)
  {
    data.trim();
    Serial.println(data);
    if (data == "hello/1"){
      digitalWrite(redLed,1);
    }

    if (data == "hello/0"){
      digitalWrite(redLed,0);
    }
    data = "";
    stringComplete = false;
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
