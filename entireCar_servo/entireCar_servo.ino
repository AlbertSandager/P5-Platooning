#include <TimerOne.h>

#define feedback_PIN A0
#define PWM_PIN 9
const float theta_base_ref = 30;
float theta_ref = theta_base_ref;
int square_count = 0;
unsigned long t0 = 0;
const unsigned long ts = 5;

float output = 45;
float lastoutput = 45;
float feedback = 40;
float lastfeedback = 40;
float T = 0.005;
float PWM_OUT = 0;

float x1 = 0;
float x2 = 0;
float x3 = 0;
float x4 = 0;

float lastx1 = 0;
float lastx2 = 0;
float lastx3 = 0;
float lastx4 = 0;

float L = 0.4;
float l = 0.3;
float v = 2;
float tau = 0.1;
float K = 1.1;
float Kp = 5;
float Kv = 5;
float ref = 0;
float lastref = 0;

float pos = 0;
float lastpos = 0;
float velocity = 0;
float lastvelocity = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(PWM_PIN, OUTPUT);
  Timer1.initialize(2000);
  Timer1.stop();
  Timer1.restart();
  t0 = millis();
  Timer1.pwm(PWM_PIN, 50, 20000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Generate square wave for reference
  if (square_count > 1600) {
    square_count = 0;
  }
  else {
    square_count++;
  }

  // Hookup reference to square wave
  if (square_count < 800) {
    theta_ref = theta_base_ref - 15;
  }
  else {
    theta_ref = theta_base_ref + 15;
  }
  float feedback = analogRead(feedback_PIN);

  if (feedback < 55) feedback = 55;
  if (feedback > 255) feedback = 255;

  //nyt
  feedback = feedback - 155;
  feedback = map(feedback, -100, 100, 0, 65);

  x1 = lastx1 + T*lastx2;
  x2 = lastx2 + T*lastx4;
  x3 = lastx3 + T*lastx4;
  x4 = lastx4-((100*L*l*tau+10*L*l+10*K*Kv*L*l)/(tau*10*L*l))*(x3-lastx3)-((100*K*Kv*L*l+100*L*l)/(10*L*l*tau))*(x2-lastx2)-((10*K*Kp*l*v+10*K*Kp*L*v)/(10*L*l*tau ))*(x1-lastx1)-((K*Kp*L*v + K*Kp*l*v)/(10*L*l*tau ))*lastx1*T+((10*K*Kp*L*v + 10*K*Kp*l*v)/(10*L*l*tau))*(ref-lastref)+((K*Kp*L*v + K*Kp*v*l)/(10*L*l*tau ))*lastref*T;
  
  lastx1 = x1;
  lastx2 = x2;
  lastx3 = x3;
  lastx4 = x4;
  lastref = ref;
  
  if(x1 < 0) x1 = 0;
  if(x1 > 65) x1 = 65;
  PWM_OUT = map(x1, 0, 65, 30, 61);

  Timer1.setPwmDuty(PWM_PIN, PWM_OUT);

  Serial.print(x1);
  Serial.print(",");
  Serial.print(theta_ref);
  Serial.print(",");
  Serial.print(PWM_OUT);
  Serial.print("\n");

  // Wait
  while ((t0 + ts) > millis()) {}
  t0 = millis();

}
