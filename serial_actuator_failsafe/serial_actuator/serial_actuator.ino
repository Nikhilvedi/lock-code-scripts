#include <Servo.h>

const int red = 13;
const int green = 12;
const int button =10;
int position = 0;
int buttonstate =1;

void setup() {
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(green, OUTPUT);
pinMode(red,OUTPUT);
pinMode(button,INPUT);

Serial.begin(9600);
  Serial.println("** Ready **");
}

void loop() {
  buttonstate= digitalRead(button);
  digitalWrite(button,HIGH);
  if (Serial.available() > 0) {
   char inChar = (char)Serial.read();
if(inChar == 'l') {  //lock
    Serial.println("Lock Door");
  setDir(2);
  slide(3); 
}
else if(inChar == 'u') { 
    Serial.println("Unlock Door");
  setDir(1);
  slide(3);
}
}
if (buttonstate == LOW) { 
   Serial.println("Unlock Door via failsafe");
  setDir(1);
  slide(3);
  delay(20000); //wait 20 seconds and lock again 
   setDir(2);
  slide(3);
}
}

void setDir(int d) {
  switch(d) {
    case 0: // off?
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
    break;
    case 1: // forward
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
    flashlights(1);
    break;
    case 2:  // backward
    digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
   flashlights(0);
    break;
    case 3:  // locked?
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    break;
  }
}

void flashlights(int colour)
{
  if (colour == 1)
  {
   digitalWrite(green, HIGH);
    delay(100);
     digitalWrite(green, LOW);
       delay(100);
      digitalWrite(green, HIGH);
    delay(100);
     digitalWrite(green, LOW);
       delay(100);
      digitalWrite(green, HIGH);
    delay(100);
     digitalWrite(green, LOW);
       delay(100);
      digitalWrite(green, HIGH);
    delay(100);
     digitalWrite(green, LOW);
}
else if (colour == 0)
{
    digitalWrite(red, HIGH);
    delay(100);
     digitalWrite(red, LOW);
      delay(100);
        digitalWrite(red, HIGH);
    delay(100);
     digitalWrite(red, LOW);
      delay(100);
        digitalWrite(red, HIGH);
    delay(100);
     digitalWrite(red, LOW);
      delay(100);
        digitalWrite(red, HIGH);
    delay(100);
     digitalWrite(red, LOW);
      delay(100);
}
}

// gradually speed up, then gradually slow down.
void slide(int d) {
  for(int v=0;v<200;++v) {
    analogWrite(3,v);
    delay(d);   
  }
  for(int v=200;v>=0;--v) {
    analogWrite(3,v);  
    delay(d);
  }
}
