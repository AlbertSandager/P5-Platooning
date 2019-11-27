#include <TimerOne.h>

#define feedback_PIN A0
#define PWM_PIN 9
#define PWM_MOTOR 10
const float theta_base_ref = 30;
float theta_ref = theta_base_ref;
int square_count = 0;
unsigned long t0 = 0;
const unsigned long ts = 5;
int motorspeed= 1;

float output = 45;
float lastoutput = 45;
float feedback = 40;
float lastfeedback = 40;
float T = 0.005;
float PWM_OUT = 0;

float KP = 10;

float pos = 0;
float lastpos = 0;
float velocity = 0;
float lastvelocity = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  Timer1.initialize(2000);
  Timer1.stop();
  Timer1.restart();
  t0 = millis();
  Timer1.pwm(PWM_PIN, 50, 20000);
  
}

void loop() {
  
  drive();
  
  
     if (Serial.available()) {
        theta_ref = Serial.read();
        theta_ref = map(theta_ref,0,65,15,50);
//        Serial.print("The following char was received: ");
//        Serial.println(theta_ref,DEC);
    }
    
  pos = lastpos + T*lastvelocity*KP;
  velocity = -(pos - lastpos) - lastpos * T*KP + theta_ref * T*KP + lastvelocity;

  lastpos = pos;
  lastvelocity = velocity;

  if(pos < 0) pos = 0;
  if(pos > 65) pos = 65;
  PWM_OUT = map(pos, 0, 65, 30, 61);

  Timer1.setPwmDuty(PWM_PIN, PWM_OUT);

//  Serial.print(pos);
//  Serial.print(",");
//  Serial.print(theta_ref);
//  Serial.print(",");
//  Serial.print(PWM_OUT);
//  Serial.print("\n");

  // Wait
  while ((t0 + ts) > millis()) {}
  t0 = millis();

}

void drive() {
  
  if (digitalRead(5) == LOW) {
    digitalWrite(10, LOW);
   delayMicroseconds((motorspeed * 4500));
   digitalWrite(10, HIGH);
    delayMicroseconds(motorspeed);
  }
  else{
    
    digitalWrite(10, LOW);
}
}
