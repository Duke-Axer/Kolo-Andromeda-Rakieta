#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 4             // deklaracja wejść analogowych joysticka w osi X
#define LED_COUNT 24 

#define joyX A0           // deklaracja wejść analogowych joysticka w osi X
#define joyY A1           // deklaracja wejść analogowych joysticka w osi Y

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

  // Serial.print(digitalRead(endstop_winda));Serial.print("winda - rakieta\t");Serial.println(digitalRead(endstop_rakieta));
//Serial.println(digitalRead(2));

///////// określanie kierunku ruchu silników //////////////

  if(yValue>600){kierunek_winda_memory = LOW; digitalWrite(dirPin_winda,kierunek_winda_memory); }
  if(yValue<450){kierunek_winda_memory = HIGH; digitalWrite(dirPin_winda,kierunek_winda_memory); }

  if(xValue>600){kierunek_rakieta_memory = HIGH; digitalWrite(dirPin_rakieta,kierunek_rakieta_memory); }
  if(xValue<450){kierunek_rakieta_memory = LOW; digitalWrite(dirPin_rakieta,kierunek_rakieta_memory); }
  

///////////////////////////////////////////////////////////
/////////////sterowanie windą /////////////////////////////
///////////////////////////////////////////////////////////
if (digitalRead(endstop_winda)==true)
    {
    if(yValue>600||yValue<450)
      {
   krok_winda();
      }
    }
if (digitalRead(endstop_winda)==false && digitalRead(dirPin_winda) == LOW)
    {
krok_winda();
    }
///////////////////////////////////////////////////////////
///////////////sterowanie rakietą//////////////////////////
///////////////////////////////////////////////////////////

if(xValue>600||xValue<450)
  {
    digitalWrite(red_button,HIGH);
    
    krok_rakieta();
  
    digitalWrite(red_button,LOW);
  }

if (digitalRead(joystick_button)==false)
{kierunek_rakieta_memory = !kierunek_rakieta_memory; digitalWrite(dirPin_rakieta,kierunek_rakieta_memory); 
  /* code */
////digitalWrite(2,HIGH);
for(int i = ring.numPixels(); i >= -2; i--){
    ring.setPixelColor(i, 100, 0, 0, 0);
    ring.setPixelColor(i-1, 0, 100, 0, 0);
    ring.setPixelColor(i-2, 0, 0, 0, 0);
    ring.show();
    delay(10);}
do
{
 krok_rakieta();
} while (digitalRead(endstop_rakieta)==false );
for(int i = ring.numPixels(); i >= -2; i--){
    ring.setPixelColor(i-2, 0, 0, 0, 0);
    ring.show();
    delay(10);}

}

//Serial.println(digitalRead(red_button));
//////////////////////////////////////////////
if (digitalRead(red_button)==0)
{  if (licznik==1){aktualnyCzas = millis();}
  licznik++;
 if (licznik==100){aktualnyCzas2 = millis() - aktualnyCzas; Serial.println(aktualnyCzas2);}
 if (licznik>=100)
{
    time_silniki_rakieta = 2;
   for(int j= 1;j <=4; j++){for(int i = 0; i< 400; i++){krok_rakieta();}delay(250);}
   aktualnyCzas2 = millis() - aktualnyCzas; Serial.println(aktualnyCzas2);
   Serial.println(licznik);
   Serial.println("Koniec obrotu");
 }
//Serial.println(licznik);
}


if (digitalRead(red_button)==1)
{licznik = 0;}

  }

  void krok_rakieta()
  {

  digitalWrite(stepPin_rakieta,HIGH); 
  delay(time_silniki_rakieta); 
  digitalWrite(stepPin_rakieta,LOW); 
  delay(time_silniki_rakieta); 

  }

   void krok_winda()
  {

  digitalWrite(stepPin_winda,HIGH); 
  delay(time_silniki_winda); 
  digitalWrite(stepPin_winda,LOW); 
  delay(time_silniki_winda); 

  }