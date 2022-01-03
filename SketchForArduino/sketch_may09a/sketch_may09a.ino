#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_NeoPixel.h"
#include <string.h>
#include <stdio.h>
#include "Parser.h"


#define TPin A1       // пин датчика температуры
#define sensorPin A3  // пин датчика уровня
#define MSPin A5      // пин датчика влажности
#define sensorPower 2
#define LED_COUNT 2
#define LED_PIN 10    // пин ленты
#define servoPin 11   // пин сервопривода

Servo Servo1;

OneWire TempValue(TPin);
DallasTemperature TSensor(&TempValue);

   int MSValue=0;  
  
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
    }
   
void loop()
{ 

   int data[10];
   int counter = 0;
   if ((Serial.available()>1 /*& (am & millis() - tmr >50)*/)){
     char str[30];
     int amount = Serial.readBytesUntil(';',str,30);   
    str[amount] = NULL;

     Parser cata(str,',');
     int am = cata.split();     //Разделить входящее сообщение на команду и параметры
     for (int i =0; i<am;i++) data[i] = atoi(cata[i]);

   
  }
  
  //int data[4];
  //char str[30];
  //if(Serial.available()){
    //int amount = Serial.readBytesUntil(';',str,30);
    //str[amount] = NULL;
    
  //}
  // we need init_state = readyRead 
  //wait for incoming msg
  //wait for stop symb
  //parse all
  //react for commands
  //  IF (HAVE OUTCOME MSG){ send msg; send stop symb;}
  //  ELSE {send stop symb (ONCE)}
  

  String vals;
  
  switch (data[0]){
    case(1): Servo1.write(data[1]); data[0] = ' '; break; 
    case(2): 
      for (int i = 0; i < LED_COUNT; i++)
      {
        strip.setPixelColor(i, strip.Color(data[1],data[2],data[3]));        
      }
      strip.show();
      data[0] = ' ';
      break;
    case(6):
      TSensor.requestTemperatures();
      float TValue = TSensor.getTempCByIndex(0);
      

      digitalWrite(sensorPower, HIGH);    // Включить датчик
      delay(10);                          // Ждать 10 миллисекунд
      int level = analogRead(sensorPin);  // Прочитать аналоговое значение от датчика
      digitalWrite(sensorPower, LOW);     // Отключить датчик

      int MSValue = analogRead(MSPin);
      float MSconv = MSValue * 0.073;
      
      vals = (String(TValue) + ',' + String(level) + ',' + String(MSconv) );

      Serial.println(vals);
      data[0] = ' ';       
    break;
    default: break;
      
  }

}
  
    
