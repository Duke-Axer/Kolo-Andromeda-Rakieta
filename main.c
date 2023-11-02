#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 4             // deklaracja wejść analogowych joysticka w osi X
#define LED_COUNT 24 

#define joyX A0             // deklaracja wejść analogowych joysticka w osi X
#define joyY A1     

const int stepPin_obrot = 6; 
const int dirPin_winda = 5; 

const int stepPin_winda = 8; 
const int dirPin_rakieta = 7; 

int i = 0;
const int kont_90 = 100;

Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

  int licznik = 0;

void setup() {
 Serial.begin(9600);       // aktywowanie połączenia MCU <=> PC (USB)

  pinMode(stepPin_obrot,OUTPUT); 
  pinMode(dirPin_winda,OUTPUT);

  pinMode(stepPin_winda,OUTPUT); 
  pinMode(dirPin_rakieta,OUTPUT);


  ring.begin();
  ring.show();
  ring.setBrightness(50);

}
 

void loop() {
 int yValue = analogRead(joyX);  // odczytaj wartość z wejścia analogowego oś X joysticka
 int xValue = analogRead(joyY);  // odczytaj wartość z wejścia analogowego oś Y joysticka


  if(xValue>600){digitalWrite(dirPin_winda,LOW); }
  if(xValue<450){digitalWrite(dirPin_winda,HIGH); }

    if(yValue>600){digitalWrite(dirPin_rakieta,LOW); }
  if(yValue<450){digitalWrite(dirPin_rakieta,HIGH); }
int time_silniki_obrot = 20;  // rakieta
int time_silniki_winda = 1; // winda



if(xValue>600||xValue<450)
  {
    for (i=0; i<kont_90;i++)
{
    digitalWrite(stepPin_obrot,HIGH); 
    delay(time_silniki_obrot); 
    digitalWrite(stepPin_obrot,LOW); 
    delay(time_silniki_obrot); 
   
}
  }
  i=0;


  if((xValue>600||xValue<450)&& false)
  {
    digitalWrite(stepPin_obrot,HIGH); 
    delay(time_silniki_obrot); 
    digitalWrite(stepPin_obrot,LOW); 
    delay(time_silniki_obrot); 
  }
  if((yValue>600||yValue<450)&& false)
  {
    digitalWrite(stepPin_winda,HIGH); 
    delay(time_silniki_winda); 
    digitalWrite(stepPin_winda,LOW); 
    delay(time_silniki_winda); 
  
  }
}