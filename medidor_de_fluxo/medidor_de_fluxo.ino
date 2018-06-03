//-------------------------------------------------------------------------------
//LiquidCrystal Library
//-------------------------------------------------------------------------------
/*
  The circuit:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 7
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 9
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int pulse_count = 0; //Variável para a quantidade de pulsos
float L = 0; //water volume
float set_L = 0; //water limit
double encoder_L;//encoder L setting
int percent = 0;

//-------------------------------------------------------------------------------
//Interface
//-------------------------------------------------------------------------------

#include "RotaryEncoder.h"

RotaryEncoder encoder(A3, A2);
int value = 0;
int newPos = 0;

//button variables
int buttonState1  = 0;
int buttonState2  = 0;
int buttonState3  = 0;
int lastButtonState1 = 0;
int lastButtonState2 = 0;
int lastButtonState3 = 0;

float mult = 1;//used as a multiplication scaler fot ser the encoder reads

//valve
bool valve = LOW;

//
int i = 0;
//

void setup() {
  Serial.begin(115200);
  Serial.println("Initialization");
  // set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	
	// Print a message to the LCD.
	lcd.setCursor(0, 0);
	lcd.print("Medidor de fluxo");

  //Waterfluxmeter
	pinMode(2, INPUT);
	attachInterrupt(0, int_pulso, RISING); //interrupt pin D2(int0)
  
  //Encoder
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, OUTPUT);
  digitalWrite(A4, HIGH);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  delay(1000);
  Serial.println("Initialization Done");
}

void loop() {
  //check if the button is pressed
  buttonState1 = digitalRead(A5);
  buttonState2 = digitalRead(11);
  buttonState3 = digitalRead(10);
  //read encoder
  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();
  //check for encoder alterations
  if (pos != newPos) {
   encoder_L = encoder_L + (newPos-pos)*mult;
   if(encoder_L < 0){
   encoder_L = 0;
   }
   pos = newPos;
  }
  //multiplication factor for the encoder
  if (buttonState1 == 0 and lastButtonState1 == 1) {
    if(mult == 1){
      mult = 10;
    }else if (mult == 10){
      mult = 0.1;
    }else if (mult == 0.1){
      mult = 1;
    }
  }
  if (buttonState2 != lastButtonState2) {
    set_L = encoder_L;
    delay(100);
  }

  if (buttonState3 != lastButtonState3) {
    set_L = 0;
    percent = 0;
    pulse_count = 0;
    digitalWrite(A4, HIGH);
    delay(100);
  }
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
  lastButtonState3 = buttonState3;
 
  //flux routine
	L = pulse_count/5.6;
  if(set_L > 0){
    percent = map(L, 0, set_L, 0 ,100); 
  }else{
    percent = 0;
  }

  if(percent >= 100 or set_L == 0){
     digitalWrite(A4, HIGH);
  }else{
     digitalWrite(A4, LOW);
  }
  i++;
  if(i>10000){
   serial_print();
   LCD_print();
   i=0;
  }
}

void LCD_print() {
 lcd.clear();
 lcd.print("Set=");
 lcd.print(encoder_L,DEC);
 lcd.setCursor(8, 0);
 lcd.print(" L=");
 lcd.print(L,DEC);
 lcd.setCursor(15, 0);
 lcd.print(" ");
 
 lcd.setCursor(0, 1);
 lcd.print("[");
 int end_bar = 10;
 while(end_bar < percent){
 lcd.print("=");
 end_bar += 10;
 }
 lcd.setCursor(11, 1);
 lcd.print("]");
 lcd.print(percent,DEC);
 lcd.setCursor(15, 1);
 lcd.print("%");
}

void serial_print(){
  Serial.print("L :");
  Serial.print(L);
  Serial.print("  %: ");
  Serial.print(percent);
  Serial.print("  encoder: ");
  Serial.print(encoder_L);
  Serial.print("  set_L: ");
  Serial.print(set_L);
  Serial.print("  mult: ");
  Serial.println(mult);
  delay(10);
  }

void int_pulso(){
	pulse_count++; //increment with pulse
}

