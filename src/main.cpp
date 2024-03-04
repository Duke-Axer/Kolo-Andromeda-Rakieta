#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 4             // deklaracja wejść analogowych joysticka w osi X
#define LED_COUNT 24 

#define joyX A0           // deklaracja wejść analogowych joysticka w osi X
#define joyY A1           // deklaracja wejść analogowych joysticka w osi Y

// millis() resetune się po 49,7 dniach 
unsigned long int time_y_delay = 0; // +1000 na delay
unsigned long int time_x_delay = 0;

bool can_y = true; // czy ma sprawdzać warość joy
bool can_x = true;

const int red_button = 2;
const int joystick_button = 3;

const int dirPin_rakieta = 5; // deklaracja kierunku ruchu rakiety
const int stepPin_rakieta = 6; // deklaracja pinu sygnałowego kroku rakiety
const int dirPin_winda = 7;   // deklaracja kierunku ruchu windy
const int stepPin_winda = 8;  // deklaracja pinu sygnałowego kroku windy

const int endstop_rakieta = 9;
const int endstop_winda = 10;

unsigned long aktualnyCzas = 0;
unsigned long aktualnyCzas2 = 0;

Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // deklacja pierściena ledowego

int licznik = 0;
int time_silniki_winda = 1;
int time_silniki_rakieta = 1;

bool kierunek_winda_memory = false;
bool kierunek_rakieta_memory = false;

void krok_rakieta();
void krok_winda();

void setup() {
  Serial.begin(9600);       // aktywowanie połączenia MCU <=> PC (USB)

  pinMode(stepPin_winda,OUTPUT);  
  pinMode(dirPin_winda,OUTPUT);

  pinMode(stepPin_rakieta,OUTPUT); 
  pinMode(dirPin_rakieta,OUTPUT);

  pinMode(red_button,INPUT_PULLUP); // przycisk red button
  pinMode(joystick_button,INPUT_PULLUP); // przycisk joysticka
  pinMode(endstop_rakieta,INPUT_PULLUP); // krańcówka rakiety
  pinMode(endstop_winda,INPUT_PULLUP); // krańcówka windy
  pinMode(11,INPUT_PULLUP); // nie podpięte
  pinMode(12,INPUT_PULLUP); // nie podpięte
  pinMode(13,OUTPUT);       // sterowanie podświetleniem red button

  ring.begin();
  ring.show();
  ring.setBrightness(50);



}

void loop() {
  int xValue = analogRead(joyX);  // odczytaj wartość z wejścia analogowego oś X joysticka
  int yValue = analogRead(joyY);  // odczytaj wartość z wejścia analogowego oś Y joysticka

///////// określanie kierunku ruchu silników //////////////
  // Działa joy
  if(yValue>600 && can_y && (millis()> time_y_delay) ){ 
    digitalWrite(dirPin_winda, HIGH); // kierunek rakiety y
    can_y = false;
    digitalWrite(stepPin_winda,HIGH); 
    time_y_delay = millis() + 1000;

    Serial.println("yValue>600"); //Wysyłanie w pętli
    }
  if(yValue<450 && can_y && (millis()> time_y_delay) ){
    digitalWrite(dirPin_winda, LOW); // kierunek rakiety y
    can_y = false;
    digitalWrite(stepPin_winda,HIGH); 
    time_y_delay = millis() + 1000;

    Serial.println("yValue<450"); //Wysyłanie w pętli
    }

  if(xValue>600 && can_x && (millis()> time_x_delay) ){
    digitalWrite(dirPin_rakieta, LOW); // kierunek rakiety x
    can_x = false;
    digitalWrite(stepPin_rakieta,HIGH); 
    time_x_delay = millis() + 1000;

    Serial.println("xValue>600"); //Wysyłanie w pętli
    }
  if(xValue<450 && can_x && (millis()> time_x_delay) ){
    digitalWrite(dirPin_rakieta, HIGH); // kierunek rakiety x
    can_x = false;
    digitalWrite(stepPin_rakieta,HIGH); 
    time_x_delay = millis() + 1000;

    Serial.println("xValue<450"); //Wysyłanie w pętli
    }

  
  if ((millis() - time_x_delay) >= 0 )
  {
  digitalWrite(stepPin_rakieta,LOW); 
  delay(time_silniki_rakieta);
  can_x = true;
  time_x_delay = millis() + 1000;
  }

  if ((millis() - time_y_delay) >= 0 )
  {
  digitalWrite(stepPin_winda,LOW); 
  delay(time_silniki_winda);
  can_y = true;
  time_y_delay = millis() + 1000;
  }
}

