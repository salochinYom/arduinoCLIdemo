#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  //setup the pin
  pinMode(13, OUTPUT);
  //setup the serial output that goes to the computer
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  //blink intergrated led on pin 13 and print hello every 2sec
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);

  Serial.print("hello \n");
}