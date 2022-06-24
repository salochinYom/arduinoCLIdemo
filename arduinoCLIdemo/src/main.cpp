#include <Arduino.h>
#include <Timer.h>

//led
Timer ledTimer(1000);
bool LEDstate = HIGH;

//serial parser
char SerialMessage[1000]; //contains text
unsigned int SerialMessagePosition = 0; //stores index position.

char SerialWordBank[20][64]; //contains words parsed from serial message;
unsigned int wordPos = 0; //tracks words in messages
unsigned int letterPos = 0;//tracks letters in words


void setup() {
  // put your setup code here, to run once:
  //setup the pin
  pinMode(13, OUTPUT);
  //setup the serial output that goes to the computer
  Serial.begin(9600);
  //Serial.setTimeout(1);
}

void loop() {
  // put your main code here, to run repeatedly:

  //blink intergrated led on pin 13 print hello every 2sec
  if(ledTimer.isExpired()){
    digitalWrite(13, LEDstate);
    //invert state
    LEDstate = !LEDstate;
  }

  //repeats what is sent to it.
  if (Serial.available() > 0) {
    char inChar = Serial.read();
    if(inChar == '\n'){ //enter
      //print
      Serial.print("\n recieved command: ");
      Serial.println(SerialMessage);
      //reset counter
      SerialMessagePosition = 0;
    }
    else{
      Serial.print(inChar);
      //store the char for later parsing
      SerialMessage[SerialMessagePosition] = inChar;
      //increment counter
      SerialMessagePosition++;
    }

  }
  //Serial.print("hello \n");
}