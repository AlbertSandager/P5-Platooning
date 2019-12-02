//#include <TimerOne.h>

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
float v = 1;
float tau = 0.1;
float K = 1.1;
float Kp = 5;
float Kv = 5;
float ref = 15;
float lastref = 15;

const byte dcMotor = 3;  // Timer 2 "B" output: OC2B

const byte servo = 10;  // Timer 2 "B" output: OC2B

const long frequency_motor = 20000L;  // Hz

const long frequency_Servo =50L;

float DUTY = 2.7;
float DUTY_DC = 0;
float toPWM = (1 / DUTY) * 100;
float toPWM_DC = 0;

float IRdistance = 30;
int distanceCounter = 0;
int button = 5;

// Variables for measuring velocity
unsigned long tstart = 0;
unsigned long tstop = 0;
unsigned long tlast = 0;
double circumference = 0.2765; //27,65 cm
double magnets = 4.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);/*
  pinMode(PWM_PIN, OUTPUT);
   Timer1.initialize(2000);
   Timer1.stop();
   Timer1.restart();
   
   Timer1.pwm(PWM_PIN, 50, 20000);*/

  t0 = millis();
  pinMode (dcMotor, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode ( servo, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)


  TCCR2A = bit (WGM20) | bit (WGM21) | bit (COM2B1); // fast PWM, clear OC2B on compare

  TCCR2B = bit (WGM22) | bit (CS21);         // fast PWM, prescaler of 8

  OCR2A =  ((F_CPU / 8) / frequency_motor) - 1;    // zero relative

  OCR2B = ((OCR2A + 1) / toPWM) - 1;             // 50% duty cycle



  TCCR1A = bit (WGM11) | bit (WGM10) | bit (COM1B1); // fast PWM, clear OC2B on compare

  TCCR1B = bit (WGM13) | bit (CS21);         // fast PWM, prescaler of 8

  OCR1A =  ((F_CPU / 16) / frequency_Servo) - 1;    // zero relative

  OCR1B = ((OCR1A + 1) / toPWM) - 1;             // 50% duty cycle*/
}

void loop() {
  if (Serial.available()) {
    ref = Serial.read();
    //ref = map(ref,0,320,0,65);
    //Serial.print("The following char was received: ");
    //Serial.println(ref,DEC);
  }

  servoLoop();
  dcmotorLoop();
  //Timer1.setPwmDuty(PWM_PIN, PWM_OUT);
  /*
  Serial.print(x1);
   Serial.print(",");
   Serial.print(ref);
   Serial.print(",");
   Serial.print(PWM_OUT);
   Serial.print("\n");
   */
  // Wait

  distanceCounter++;
  if(distanceCounter == 8){
    int sensorValue = analogRead(A1);
    IRdistance = 187754 * pow(sensorValue, -1.51);
    L = IRdistance/100;
    distanceCounter = 0; 
  }
  t0 = millis();
  
  float interval = (tstart - tlast);
  float velocity;
  velocity = ((circumference / magnets) / (interval / 1000)) * 3.6;
  //v = velocity*3;
  

    while ((t0 + ts) > millis()) {
  }

}

void servoLoop(){
    Serial.print(L);
  Serial.print(',');
  Serial.print(l);
  Serial.print(',');
  Serial.print(v);
  Serial.print(',');
  Serial.print(tau);
  Serial.print(',');
  Serial.print(K);
  Serial.print(',');
  Serial.print(Kp);
  Serial.print(',');
  Serial.print(Kv);
  Serial.print(',');
  Serial.print(ref);
  Serial.print(',');
  Serial.print(x1);
  Serial.print(',');
  Serial.println(lastref);
 /* float L = 0.4;
  float l = 0.3;
  float v = 6;
  float tau = 0.1;
  float K = 1.1;
  float Kp = 5;
  float Kv = 5;
  float ref = 15;
  float lastref = 15;*/
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
  DUTY = map(x1, 0, 65, 320, 570);
  DUTY = DUTY/100;
  if(DUTY < 2.7) DUTY = 2.7;
  if(DUTY > 6) DUTY = 6;

  //DUTY = 4.3; //remove this

  toPWM = (1 / DUTY) * 100;

  OCR1B = ((OCR1A + 1) / toPWM) - 1;
}

void dcmotorLoop(){
  
  if(digitalRead(button) == LOW){
    DUTY_DC = 20;
    toPWM_DC = (1 / DUTY_DC) * 100;

    OCR2B = ((OCR2A + 1) / toPWM_DC) - 1;
    Serial.println("ALT GODT");
  }
  else {
    toPWM_DC = 0;

    OCR2B = ((OCR2A + 1) / toPWM_DC) - 1;
  }
}

void magnet_detect() {
  tlast = tstart;
  tstart = millis();
 
}

