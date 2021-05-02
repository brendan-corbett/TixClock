#include <RTClib.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel hours1(3, 13);
Adafruit_NeoPixel hours2(9, 11);
Adafruit_NeoPixel minutes1(9, 9);
Adafruit_NeoPixel minutes2(9, 6);

int butPin = 3;
boolean butState = LOW;
boolean prevButState = LOW;

RTC_DS3231 rtc;
int tHour;
int tMin;
int tSec;
String dayT;
const int avoidVals[] = {4, 14, 24};
uint32_t color1;// = strip.Color(255,0,0);
uint32_t color2;
uint32_t color3;
uint32_t color4;

uint32_t randoColor1;
uint32_t randoColor2;
uint32_t randoColor3;
uint32_t randoColor4;

int switchVal = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
DateTime now;

long startTime;
long endTime;
int interval = 1000;

long startTime2;
long endTime2;
int interval2 = 15000;

long startTime3;
long endTime3;

int interval3 = 500;


int hoursC;
int minsC;
int secsC;
int daysC;

int dayVal;

int hours1Show;
int minutes1Show;
int hours2Show;
int minutes2Show;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(butPin, INPUT);
  hours1.begin();
  hours1.setBrightness(50);
  hours1.clear();
  hours1.show();

  hours2.begin();
  hours2.setBrightness(50);
  hours2.clear();
  hours2.show();

  minutes1.begin();
  minutes1.setBrightness(50);
  minutes1.clear();
  minutes1.show();

  minutes2.begin();
  minutes2.setBrightness(50);
  minutes2.clear();
  minutes2.show();

  startTime = millis();
  startTime2 = millis();
  startTime3 = millis();


  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  endTime = millis();
  endTime2 = millis();
  endTime3 = millis();
  
  butState = debounce(butPin, butState);
  if (butState == HIGH && prevButState == LOW)
  {
    Serial.println("Debounce press");
    switchVal++;
    if (switchVal > 3)
    {
      switchVal = 0;
    }

  }
  prevButState = butState;

  switch (switchVal)
  {
    case 0:
      if (endTime - startTime >= interval)
      {
        getTime();
        convertColorS();
        changeColorD();
        //       Serial.println("Case 0");
        startTime = millis();
      }
      break;

    case 1:
      if (endTime - startTime >= interval)
      {
        getTime();
        convertColorD();
        changeColorD();
        startTime = millis();
        //       Serial.println("Case 1");
      }
      break;

    case 2:
      if (endTime2 - startTime2 >= interval)
      {
        getTime();
        if (endTime3 - startTime3 >= interval2)
        {
          randomColor();
          startTime3 = millis();
        }
        changeColorRandom();
        startTime2 = millis();
        //       Serial.println("Case 2");
      }
      break;

    case 3:
      if (endTime2 - startTime2 >= interval3)
      {
        getTime();
        randomColor();
        changeColorRandom();
        startTime2 = millis();
        //       Serial.println("Case 3");
      }
      break;
  }
}

void getTime()
{
  now = rtc.now();
  tHour = now.hour();
  tMin = now.minute();
  tSec = now.second();
  dayT = now.day();

  if (tHour < 10)
  {
    hours2Show = tHour;
  }
  else if (tHour < 20)
  {
    hours1Show = 1;
    hours2Show = tHour - 10;
  }
  else if (tHour >= 20)
  {
    hours1Show = 2;
    hours2Show = tHour - 20;
  }

  if (tMin < 10)
  {
    minutes2Show = tMin;
  }
  else if (tMin < 20)
  {
    minutes1Show = 1;
    minutes2Show = tMin - 10;
  }
  else if (tMin < 30)
  {
    minutes1Show = 2;
    minutes2Show = tMin - 20;
  }
  else if (tMin < 40)
  {
    minutes1Show = 3;
    minutes2Show = tMin - 30;
  }
  else if (tMin < 50)
  {
    minutes1Show = 4;
    minutes2Show = tMin - 40;
  }
  else if (tMin < 60)
  {
    minutes1Show = 5;
    minutes2Show = tMin - 50;
  }

  //
  Serial.print("Hour: ");
  Serial.println(tHour);
  Serial.print("Minute: ");
  Serial.println(tMin);
  
  //  Serial.print("1st slot: ");
  //  Serial.println(hours1Show);
  //
  //  Serial.print("2nd slot: ");
  //  Serial.println(hours2Show);
  //
  //  Serial.print("3rd slot: ");
  //  Serial.println(minutes1Show);
  //
  //  Serial.print("4th slot: ");
  //  Serial.println(minutes2Show);
}

void changeColorD()
{
  hours1.clear();
  hours2.clear();
  minutes1.clear();
  minutes2.clear();

  for (int a = 0; a < hours1Show; a++)
  {
    hours1.setPixelColor(a, color1);

  }

  for (int b = 0; b < hours2Show; b++)
  {
    hours2.setPixelColor(b, color2);
  }

  for (int c = 0; c < minutes1Show; c++)
  {
    minutes1.setPixelColor(c, color3);
  }

  for (int d = 0; d < minutes2Show; d++)
  {
    minutes2.setPixelColor(d, color4);
  }

  hours1.show();
  hours2.show();
  minutes1.show();
  minutes2.show();

  //  Serial.print("DaysC: "); Serial.println(daysC);
  //  Serial.print("HoursC: "); Serial.println(hoursC);
  //  Serial.print("MinutesC: "); Serial.println(minsC);
  //  Serial.print("SecondsC: "); Serial.println(secsC);
  //  Serial.print("Day of week: ");
  //  Serial.println(dayT);
  //  getDay(daysOfTheWeek[now.dayOfTheWeek()]);
  //  Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
  //  Serial.println();
}

void changeColorRandom()
{
  hours1.clear();
  hours2.clear();
  minutes1.clear();
  minutes2.clear();

  for (int a = 0; a < hours1Show; a++)
  {
    hours1.setPixelColor(a, randoColor1);
  }

  for (int b = 0; b < hours2Show; b++)
  {
    hours2.setPixelColor(b, randoColor2);
  }

  for (int c = 0; c < minutes1Show; c++)
  {
    minutes1.setPixelColor(c, randoColor3);
  }

  for (int d = 0; d < minutes2Show; d++)
  {
    minutes2.setPixelColor(d, randoColor4);
  }

  hours1.show();
  hours2.show();
  minutes1.show();
  minutes2.show();
}

void convertColorD()
{
  daysC = map(dayVal, 0, 6, 0, 255);
  hoursC = map(tHour, 0, 24, 0, 255);
  minsC = map(tMin, 0, 59, 0, 255);
  //  secsC = map(tSec, 0, 59, 0, 255);
  color1 = hours1.Color(daysC, hoursC, minsC);  //updates color every minute
  color2 = hours2.Color(daysC, hoursC, minsC);
  color3 = minutes1.Color(daysC, hoursC, minsC);
  color4 = minutes2.Color(daysC, hoursC, minsC);
}

void convertColorS()
{
  //  daysC = map(dayVal, 0, 6, 0, 255);
  hoursC = map(tHour, 0, 24, 0, 255);
  minsC = map(tMin, 0, 59, 0, 255);
  secsC = map(tSec, 0, 59, 0, 255);
  color1 = hours1.Color(hoursC, minsC, secsC);  //updates color every second
  color2 = hours2.Color(hoursC, minsC, secsC);
  color3 = minutes1.Color(hoursC, minsC, secsC);
  color4 = minutes2.Color(hoursC, minsC, secsC);
}



void getDay(String val)
{
  for (int x = 0; x < 7; x++)
  {
    if (val == daysOfTheWeek[x])
    {
      // Serial.println("Reading array");
      dayVal = x;
    }
  }
}

void randomColor()
{
  randoColor1 = hours1.Color(random(0, 255), random(0, 255), random(0, 255));
  randoColor2 = hours2.Color(random(0, 255), random(0, 255), random(0, 255));
  randoColor3 = minutes1.Color(random(0, 255), random(0, 255), random(0, 255));
  randoColor4 = minutes2.Color(random(0, 255), random(0, 255), random(0, 255));
}

boolean debounce (int buttonPin, boolean previousButtonState)
{
  boolean buttonState = digitalRead(buttonPin);

  if (buttonState != previousButtonState)
  {
    delay(50);
  }

  return buttonState;
}
