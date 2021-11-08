#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_NeoPixel.h"
#include <string.h>
#include <stdio.h>
#include "Parser.h"


#define TPin A3// пин подключения датчика температуры
#define sensorPin A1
#define MSPin A2
#define sensorPower 2
#define PumpPin 13
#define LED_COUNT 2
#define LED_PIN 5
#define servoPin 3
Servo Servo1;

OneWire TempValue(TPin);
DallasTemperature TSensor(&TempValue);

   int MSValue=0;   //  changed -> MSValue = 0;
   int pumpcomm;
  
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  Serial.begin(9600);
  //Serial.setTimeout(1000);    //changed -> nothing
  strip.begin();
  Servo1.attach(servoPin);
 // температура
  TSensor.begin();
  pinMode(TPin,INPUT);
 // уровень
    // Настраиваем D7 на выход
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  pinMode(PumpPin,OUTPUT);   
    }
   
void loop()
{ int data[10];
  int counter = 0;
/* static byte prevAm = 0;
  static uint32_t tmr = 0;
  byte am = Serial.available();
  if (am != prevAm){
    prevAm = am;
    tmr = millis();
  }*/
  if ((Serial.available()>1 /*& (am & millis() - tmr >50)*/)){
    char str[30];
    int amount = Serial.readBytesUntil(';',str,30);   // TERMINATOR = ';'
    str[amount] = NULL;

    Parser cata(str,',');
    int am = cata.split();
    for (int i =0; i<am;i++) data[i] = atoi(cata[i]);
   
    /*char  *rest = NULL;
    char *token;
    for (token = strtok_r(str,",",&rest);   //DELIMITER = ","
    token!=NULL;
    token = strtok_r(NULL,",",&rest)){
      data[counter] = atoi(token);
      counter++;  
    }*/
    
    //Servo1.write(90);
  //Serial.println(data[1]);
    //Serial.println(data[2]);
    //Serial.println(data[3]);
   
  }
  

  String vals;
  
  switch (data[0]){
    case(1): Servo1.write(data[1]); data[0] = ' '; break; 
    case(2): for (int i = 0; i < LED_COUNT; i++)
      {
        strip.setPixelColor(i, strip.Color(data[1],data[2],data[3]));
        
      }
      strip.show();
      data[0] = ' ';
      break;
    case(6):
      TSensor.requestTemperatures();
      float TValue = TSensor.getTempCByIndex(0);
      //Serial.print("6,");
          //Serial.print(TValue);
          //Serial.print(';');    
      digitalWrite(sensorPower, HIGH);  // Включить датчик
  delay(10);                        // Ждать 10 миллисекунд
  int level = analogRead(sensorPin);  // Прочитать аналоговое значение от датчика
  digitalWrite(sensorPower, LOW);
      //Serial.print("6,");
          //Serial.println(level);
          //Serial.print(';');

    int MSValue = analogRead(MSPin);
    float MSconv = MSValue * 0.073;
                            //Serial.print("Moist:");
    //Serial.print("8,");                        
        //Serial.print(MSconv);
        //Serial.print(';');
        int i = 0;
    char sendData[30];
         vals = (String(TValue) + ',' + String(level) + ',' + String(MSconv) );
       /*while (vals[i] != ';') {
           sendData[i] = vals[i];
           i++;
       }
       sendData[i] = vals[i];*/
       Serial.println(vals);
       data[0] = ' ';
       
    break;
    case(7):
    delay(data[1]);
    break;
    default: break;
    
      
  }

}
  
    
