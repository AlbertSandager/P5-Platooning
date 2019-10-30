#include <Servo.h>

Servo myservo;
int pos = 0;

void setup(){
  myservo.attach(9);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()){
    pos = Serial.read();
    Serial.print("The following char was received: ");
    Serial.println(pos,DEC);
    myservo.write(pos);
  }
}

