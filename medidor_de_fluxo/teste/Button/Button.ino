/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

int buttonState1  = 0;
int buttonState2  = 0;
int buttonState3  = 0;
int lastButtonState1 = 0;
int lastButtonState2 = 0;
int lastButtonState3 = 0;

void setup() {
  // initialize the LED pin as an output:
    Serial.begin(115200);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState6 = digitalRead(A6);
  buttonState7 = digitalRead(A7);

  if (buttonState6 == 0 and lastButtonState1 == 1) {
    if(mult == 1){
      mult = 10;
    }else if (mult == 10){
      mult = 0.1;
    }else if (mult == 0.1){
      mult = 1;
    }
  }
  if (buttonState2 != lastButtonState2) {
    set_L=encoder_L;
  }
  
  lastButtonState6 = buttonState1;
  lastButtonState7 = buttonState2;

}
