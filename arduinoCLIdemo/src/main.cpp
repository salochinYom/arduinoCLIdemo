#include <Arduino.h>
#include <Timer.h>

//led
Timer ledTimer(1000);
bool LEDstate = HIGH;

void setup() {
  // put your setup code here, to run once:
  //setup the pin
  pinMode(13, OUTPUT);
  //setup the serial output that goes to the computer
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  //blink intergrated led on pin 13 print hello every 2sec
  if(ledTimer.isExpired()){
    digitalWrite(13, LEDstate);
    //invert state
    LEDstate = !LEDstate;
  }


  Serial.print("hello \n");
}