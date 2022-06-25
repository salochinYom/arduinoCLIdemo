#include <Arduino.h>
#include <Timer.h>

//led
Timer ledTimer(1000);
bool LEDstate = HIGH;

//serial parser
#define WORD_LENG 75
#define LETTER_LENG 64 
#define MESSAGE_LENG 2000 

char SerialMessage[MESSAGE_LENG]; //contains text
unsigned int SerialMessagePosition = 0; //stores index position.

char SerialWordBank[WORD_LENG][LETTER_LENG]; //contains words parsed from serial message
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

      //parse serial message into words by " "
      //clear last command
      for(unsigned int x = 0; x < WORD_LENG; x++){
        for(unsigned int y = 0; y < LETTER_LENG; y++){
          SerialWordBank[x][y] = ' ';
        }
      }
      //reset counters
      wordPos = 0;
      letterPos = 0;
      for(unsigned int i; i < SerialMessagePosition; i++){
        if(SerialMessage[i] == ' '){ //if space
          wordPos++;
          letterPos = 0;
          SerialWordBank[wordPos][letterPos] = SerialMessage[i];
          letterPos++;
        }
        else{
          SerialWordBank[wordPos][letterPos] = SerialMessage[i];
          letterPos++;
        }
      }
      //print out words
      for(unsigned int i = 0; i <= wordPos; i++){
        for(unsigned int x = 0; x <= LETTER_LENG; x++){
          Serial.print(SerialWordBank[i][x]);
        }
        Serial.println(i);
      }

      //reset counter
      SerialMessagePosition = 0;

      //reset Serial message
      for(unsigned int i = 0; i < MESSAGE_LENG; i++){
        SerialMessage[i] == ' ';

      }
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