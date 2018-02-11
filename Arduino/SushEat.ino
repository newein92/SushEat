
#include <SoftwareSerial.h>
#define RX 10
#define TX 11
#define ROLL_ME 1
#define FOLD_ME 2

int received = 0;
int index;

SoftwareSerial mySerial (RX,TX);

  
void setup() {
// put your setup code here, to run once:
  mySerial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
//////////////////////////Rolling pin setup///////////////
  pinMode(9, OUTPUT); //Enable
  pinMode(8, OUTPUT); //Step
  pinMode(7, OUTPUT); //Direction
  digitalWrite(9,LOW);
/////////////////////////Plates setup////////////////////
  pinMode(6, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(4, OUTPUT); //Direction
  digitalWrite(6,LOW);
  pinMode(2, OUTPUT); //Enable
  pinMode(1, OUTPUT); //Step
  pinMode(0, OUTPUT); //Direction
  digitalWrite(2,LOW);
////////////////////////////////////////////////////////
}

void loop() {
   while(mySerial.available()) {
     received = mySerial.read();
     
     if(received == 187){
      mySerial.write(received);
       delay(250);
       digitalWrite(13,LOW);
       delay(100);
       mySerial.println("RESTARDED");
       digitalWrite(13,HIGH);     
     }
     else if(received == ROLL_ME){
      digitalWrite(7,false);
      for(index = 0; index < 17000; index++){
        digitalWrite(8,HIGH);
        delayMicroseconds(750);
        digitalWrite(8,LOW);
        delayMicroseconds(750);
      }
      delay(1000); 
      digitalWrite(7,true); 
      for(index = 0; index < 17000; index++){
        digitalWrite(8,HIGH);
        delayMicroseconds(750);
        digitalWrite(8,LOW);
        delayMicroseconds(750);
      }
      received = 0;             
     }
     else if(received == FOLD_ME){
      digitalWrite(4,true);
      digitalWrite(0,true);
      for(index = 0; index < 750; index++){
        digitalWrite(5,HIGH);
        digitalWrite(1,HIGH);
        delayMicroseconds(3000);
        digitalWrite(5,LOW);
        digitalWrite(1,LOW);
        delayMicroseconds(3000);
      }
      for(index = 0; index < 470; index++){
        digitalWrite(5,HIGH);
        delayMicroseconds(3000);
        digitalWrite(5,LOW);
        delayMicroseconds(3000);
      }
      delay(2000);
      digitalWrite(4,false);
      digitalWrite(0,false);
      for(index = 0; index < 750; index++){
        digitalWrite(5,HIGH);
        digitalWrite(1,HIGH);
        delayMicroseconds(3000);
        digitalWrite(5,LOW);
        digitalWrite(1,LOW);
        delayMicroseconds(3000);
      }
      for(index = 0; index < 470; index++){
        digitalWrite(5,HIGH);
        delayMicroseconds(3000);
        digitalWrite(5,LOW);
        delayMicroseconds(3000);
      }
      received = 0;                 
     }
  }
}
