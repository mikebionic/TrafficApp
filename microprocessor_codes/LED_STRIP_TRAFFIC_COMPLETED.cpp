#include <FastLED.h>

#define NUM_LEDS_1 4
#define NUM_LEDS_2 4
#define TRAFFIC1_DATA 3
#define TRAFFIC2_DATA 4

CRGB traffic1[NUM_LEDS_1];
CRGB traffic2[NUM_LEDS_2];

String data;
String dataPart1;
String dataPart2;

unsigned long currentTime = millis();
unsigned long greenTimeGreater;
unsigned long greenTimeLess;

long timeConserved1 = 0;
long timeUsing1 = 0;
long timeConserved2 = 0;
long timeUsing2 = 0;
long startTime = 0;
long elapsedTime = currentTime - startTime;
long cycleTime = 23000;

bool updateTime = true;
bool stringComplete = false;

void setup() 
{
  FastLED.addLeds<NEOPIXEL, TRAFFIC1_DATA>(traffic1, NUM_LEDS_1);
  FastLED.addLeds<NEOPIXEL, TRAFFIC2_DATA>(traffic2, NUM_LEDS_2);
  Serial.begin(9600);
}

void loop() 
{
  if(stringComplete)
  {
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
  FastLED.show();
  greenTimeGreater = timeUsing1 * 400;
  greenTimeLess = timeUsing2 * 400;
  currentTime = millis();
  elapsedTime = currentTime - startTime;
  if(timeUsing1 >= timeUsing2)
  {
    if(timeUsing1 <= 20)
    {
      if(elapsedTime < 3000)
      {
        traffic1[1] = CRGB::Yellow;
        traffic2[1] = CRGB::Yellow;
      }
      else 
      {
        traffic1[1] = CRGB::Black;
        traffic2[1] = CRGB::Black;
      }

      if (elapsedTime > 3000 && elapsedTime < 10000)
      {
        traffic1[0] = CRGB::Green;
        traffic2[2] = CRGB::Red;
      }
      else
      {
        traffic1[0] = CRGB::Black;
        traffic2[2] = CRGB::Black;
      }
    
      if (elapsedTime > 10000 && elapsedTime < 13000)
      {
        traffic1[1] = CRGB::Yellow;
        traffic2[1] = CRGB::Yellow;
      }
      else
      {
        if(elapsedTime < 3000)
        {
          traffic1[1] = CRGB::Yellow;
          traffic2[1] = CRGB::Yellow;
        }
        else
        {
          traffic1[1] = CRGB::Black;
          traffic2[1] = CRGB::Black;  
        }
      }
      if (elapsedTime > 13000)
      {
        traffic1[2] = CRGB::Red;
        traffic2[0] = CRGB::Green;
      }
      else
      {
        traffic1[2] = CRGB::Black;
        traffic2[0] = CRGB::Black;
      }
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
        traffic1[1] = CRGB::Yellow;
        traffic2[1] = CRGB::Yellow;
      }
      else
      {
        traffic1[1] = CRGB::Black;
        traffic2[1] = CRGB::Black;
      }

      if (elapsedTime > 3000 && elapsedTime < (greenTimeGreater + 3000))
      {
        traffic1[0] = CRGB::Green;
        traffic2[2] = CRGB::Red;
      }
      else
      {
        traffic1[0] = CRGB::Black;
        traffic2[2] = CRGB::Black;
      }
    
      if (elapsedTime > (greenTimeGreater + 3000) && elapsedTime < (greenTimeGreater + 6000))
      {
        traffic1[1] = CRGB::Yellow;
        traffic2[1] = CRGB::Yellow;
      }
      else
      {
        if(elapsedTime < 3000)
        {
          traffic1[1] = CRGB::Yellow;
          traffic2[1] = CRGB::Yellow;
        }
        else
        {
          traffic1[1] = CRGB::Black;
          traffic2[1] = CRGB::Black;  
        }
      }
      if (elapsedTime > (greenTimeGreater + 6000))
      {
        traffic1[2] = CRGB::Red;
        traffic2[0] = CRGB::Green;
      }
      else
      {
        traffic1[2] = CRGB::Black;
        traffic2[0] = CRGB::Black;
      }
      
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
        traffic1[1] = CRGB::Yellow;
        traffic2[1] = CRGB::Yellow;
      }
      else
      {
        traffic1[1] = CRGB::Black;
        traffic2[1] = CRGB::Black;
      }

      if (elapsedTime > 3000 && elapsedTime < 10000)
      {
        traffic1[0] = CRGB::Red;
        traffic2[2] = CRGB::Green;
      }
      else
      {
        traffic1[0] = CRGB::Black;
        traffic2[2] = CRGB::Black;
      }
    
      if (elapsedTime > 10000 && elapsedTime < 13000)
      {
        traffic1[1] = CRGB::Yellow;
        traffic2[1] = CRGB::Yellow;
      }
      else
      {
        if(elapsedTime < 3000)
        {
          traffic1[1] = CRGB::Yellow;
          traffic2[1] = CRGB::Yellow;
        }
        else
        {
          traffic1[1] = CRGB::Black;
          traffic2[1] = CRGB::Black;  
        }
      }
    
      if (elapsedTime > 13000)
      {
        traffic1[2] = CRGB::Green;
        traffic2[0] = CRGB::Red;
      }
      else
      {
        traffic1[2] = CRGB::Black;
        traffic2[0] = CRGB::Black;
      }
      
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
        traffic1[1] = CRGB::Yellow;
        traffic2[1] = CRGB::Yellow;
      }
      else
      {
        traffic1[1] = CRGB::Black;
        traffic2[1] = CRGB::Black;
      }

      if (elapsedTime > 3000 && elapsedTime < 13000)
      {
        traffic1[0] = CRGB::Red;
        traffic2[2] = CRGB::Green;
      }
      else
      {
        traffic1[0] = CRGB::Black;
        traffic2[2] = CRGB::Black;
      }
    
      if (elapsedTime > 13000 && elapsedTime < 16000)
      {
        traffic1[1] = CRGB::Yellow;
        traffic2[1] = CRGB::Yellow;
      }
      else
      {if(elapsedTime < 3000)
        {
          traffic1[1] = CRGB::Yellow;
          traffic2[1] = CRGB::Yellow;
        }
        else
        {
          traffic1[1] = CRGB::Black;
          traffic2[1] = CRGB::Black;  
        }
      }
    
      if (elapsedTime > 16000 && elapsedTime < (greenTimeLess + 16000))
      {
        traffic1[2] = CRGB::Green;
        traffic2[0] = CRGB::Red;
      }
      else
      {
        traffic1[2] = CRGB::Black;
        traffic2[0] = CRGB::Black;
      }
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
    char inChar = (char)Serial.read();
    data += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
