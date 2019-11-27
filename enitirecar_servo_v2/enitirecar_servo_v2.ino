#include <TimerOne.h>

#define feedback_PIN A0
#define PWM_PIN 9
const float theta_base_ref = 30;
float theta_ref = theta_base_ref;
int square_count = 0;
unsigned long t0 = 0;
const unsigned long ts = 5;

float T = 0.005;
float PWM_OUT = 0;


float x1 = 15;
float x2 = 0;
float x3 = 0;
float x4 = 0;

float lastx1 = 15;
float lastx2 = 0;
float lastx3 = 0;
float lastx4 = 0;

float L = 0.4;
float l = 0.3;
float v = 6;
float tau = 0.1;
float K = 1.1;
float Kp = 1;
float Kv = 5;
float ref = 15;
float lastref = 15;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PWM_PIN, OUTPUT);
  Timer1.initialize(2000);
  Timer1.stop();
  Timer1.restart();
  t0 = millis();
  Timer1.pwm(PWM_PIN, 50, 20000);
}

void loop() {
     if (Serial.available()) {
        ref = Serial.read();
        //ref = map(ref,0,320,0,65);
        //Serial.print("The following char was received: ");
        //Serial.println(ref,DEC);
    }

  x1 = lastx1 + T*lastx2;
  x2 = lastx2 + T*lastx3;
  x3 = lastx3 + T*lastx4;
  x4 = lastx4-((100*L*l*tau+10*L*l+10*K*Kv*L*l)/(tau*10*L*l))*(x3-lastx3)-((100*K*Kv*L*l+100*L*l)/(10*L*l*tau))*(x2-lastx2)-((10*K*Kp*l*v+10*K*Kp*L*v)/(10*L*l*tau ))*(x1-lastx1)-((K*Kp*L*v + K*Kp*l*v)/(10*L*l*tau ))*lastx1*T+((10*K*Kp*L*v + 10*K*Kp*l*v)/(10*L*l*tau))*(ref-lastref)+((K*Kp*L*v + K*Kp*v*l)/(10*L*l*tau ))*lastref*T;
  
  lastref = ref;
  lastx1 = x1;
  lastx2 = x2;
  lastx3 = x3;
  lastx4 = x4;
  
  
  //if(x1 < 0) x1 = 0;
  //if(x1 > 65) x1 = 65;
  PWM_OUT = map(x1, 0, 65, 30, 61);

  if(PWM_OUT < 31) PWM_OUT =31;
  if(PWM_OUT > 65) PWM_OUT = 65;
  Timer1.setPwmDuty(PWM_PIN, PWM_OUT);
/*
  Serial.print(x1);
  Serial.print(",");
  Serial.print(ref);
  Serial.print(",");
  Serial.print(PWM_OUT);
  Serial.print("\n");
*/
  // Wait
  while ((t0 + ts) > millis()) {}
  t0 = millis();

}
