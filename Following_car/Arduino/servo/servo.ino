#include <Servo.h>

Servo myservo;
int pos = 0;

int pwm = 12; // assigns pin 12 to variable pwm
unsigned long tstart = 0;
unsigned long tstop= 0;

void setup(){
  myservo.attach(9);
  Serial.begin(115200);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  tstart = millis();

}

void loop() {

  if(Serial.available()) {
      pos = Serial.read();
      Serial.print("The following char was received: ");
      Serial.println(pos,DEC);
      myservo.write(pos);
  }


  tstop = millis();
  if(tstop-tstart < 30000) {
    digitalWrite(7, HIGH);
    analogWrite(11, 25);
  }
  else {
    analogWrite(11,0);
  }

}
