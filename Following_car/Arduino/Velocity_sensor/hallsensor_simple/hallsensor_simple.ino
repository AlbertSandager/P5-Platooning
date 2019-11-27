#include <TimerOne.h>
#define PWM_PIN 10
float velocity = 0.0;
int period = 10; //100 mu-s
unsigned long time_last = 0;
double circumference = 0.2765; //27,65 cm
double magnets = 4.0;
unsigned long LOWcounter = 0;
unsigned long total_time = 0;
int last_magnetstate = 0;
unsigned long timer = 0;
unsigned long newmillis = 0;
float tstart = 0;
float tstop = 0;
int motorSpeed = 512;


void setup() {
  Timer1.initialize(2000);
  Timer1.pwm(PWM_PIN, motorSpeed, 20);
  Serial.begin(9600);
  attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
  pinMode(PWM_PIN, OUTPUT); // declares pin 12 as output
  pinMode(6, OUTPUT);  // declares pin A0 as input
  pinMode(7, OUTPUT);  // declares pin A0 as input
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  pinMode(5, INPUT_PULLUP);

}


void loop() {

  if (digitalRead(2) == LOW) {
    
    tstop = millis();

    float interval = (tstop - tstart);
    float velocity;
    velocity = ((circumference / magnets) / (interval / 1000)) * 3.6;
    Serial.println(velocity, 5);
    
  }
  drive();

}

void magnet_detect() {
  tstart = millis();
}

void drive() {
  if (digitalRead(5) == LOW) {
    Timer1.setPwmDuty(PWM_PIN, motorSpeed);
  } else if (digitalRead(5) == HIGH)  {
    Timer1.setPwmDuty(PWM_PIN, 0);
  }
}
