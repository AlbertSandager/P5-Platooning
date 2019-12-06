//#include <TimerOne.h>
#include <Servo.h>
#define feedback_PIN A0
#define PWM_PIN 9

unsigned long t0 = 0;
const unsigned long ts = 5;

float T = 0.05;
float PWM_OUT = 0;

int servocounter = 0;


float Kp = 10;
float Kv = 15;

float ref = 32;
float lastref = 32;

const byte dcMotor = 3;  // Timer 2 "B" output: OC2B

const byte servo = 10;  // Timer 2 "B" output: OC2B

const long frequency_motor = 20000L;  // Hz

const long frequency_Servo =50L;

float DUTY = 32;
float lastduty = 32;
float lastmappedduty = 0;
float theta = 32;
float lasttheta = 32;
float lasterror = 0;
float DUTY_DC = 0;
float toPWM = (1 / DUTY) * 100;
float toPWM_DC = 0;

float IRdistance = 30;
int distanceCounter = 0;
int button = 5;

float L = 0.3;
float v = 0;

float servopos = 32;
float lastservopos = 32;
float velocityfeedback = 0;

// Variables for measuring velocity
unsigned long tstart = 0;
unsigned long tstop = 0;
unsigned long tlast = 0;
double circumference = 0.2765; //27,65 cm
double magnets = 8.0;
Servo myservo;

int interruptCounter = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  myservo.attach(10);


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


  /*
  TCCR1A = bit (WGM11) | bit (WGM10) | bit (COM1B1); // fast PWM, clear OC2B on compare
   
   TCCR1B = bit (WGM13) | bit (CS21);         // fast PWM, prescaler of 8
   
   OCR1A =  ((F_CPU / 16) / frequency_Servo) - 1;    // zero relative
   
   OCR1B = ((OCR1A + 1) / toPWM) - 1;             // 50% duty cycle*/

}

void loop() {
  if (Serial.available()) {
    theta = Serial.read();
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
   if(distanceCounter == 2){
   int sensorValue = analogRead(A1);
   IRdistance = 187754 * pow(sensorValue, -1.51);
   L = IRdistance/100;
   distanceCounter = 0; 
   }
   t0 = millis();
   if(tlast != 0){
   int interval = (tstart - tlast);
   float velocity;
   velocity = ((circumference / magnets) / (interval / 1000)) * 3.6;
   v = velocity/3.6;
   Serial.print(L);
   Serial.print(',');
   Serial.println(velocity)
   /*
   if(interruptCounter >= 8){
     float velocity = micros()-tlast;
     tlast = micros();
     interruptCounter = 0;
   Serial.println(velocity);*/
 }
   
   
  while ((t0 + T*1000) > millis()) {
  }

}

void servoLoop(){
  float error = ref - theta;
  DUTY = (1-10*T)*lastduty+Kp*(0.1*T-1)*lasterror+Kp*error;
  /*Serial.print(ref);
  Serial.print(',');
  Serial.print(error);
  Serial.print(',');
  Serial.print(DUTY);*/
  lastduty = DUTY;
  lasterror = error;
  servopos = analogRead(A0);
  servopos = map(servopos, 250, 605, 0, 65);
  velocityfeedback = (Kv*(servopos-lastservopos))/T;
  lastservopos = servopos;

  if(DUTY < -5) DUTY = -5;
  else if(DUTY > 5) DUTY = 5;
  //if(error < 0){
  DUTY = DUTY*100;
  DUTY = map(DUTY, 5*100, -5*100, 0, 6500);
  //else if (error > 0){
  //DUTY = map(DUTY, -0.3*Kp, 0.3*Kp, 320, 570);}
  DUTY = DUTY/100;
  DUTY = DUTY-velocityfeedback;
  if(DUTY - lastmappedduty > 1) DUTY = lastmappedduty+1;
  else if(DUTY - lastmappedduty < -1) DUTY = lastmappedduty-1;
  lastmappedduty = DUTY;
  /*Serial.print(',');
  Serial.print(DUTY);*/

  
  if(DUTY < 0) DUTY = 0;
  if(DUTY > 65) DUTY = 65;
  servocounter++;
  int angle = DUTY;
  if(servocounter >= 2){

    myservo.write(angle);
    servocounter = 0;
  }
  /*Serial.print(',');
  Serial.println(angle);*/
  //DUTY = 4.3; //remove this

  //toPWM = (1 / DUTY) * 100;

  //OCR1B = ((OCR1A + 1) / toPWM) - 1;
}

void dcmotorLoop(){
 
 if(digitalRead(button) == LOW){
 DUTY_DC = 25;
 toPWM_DC = (1 / DUTY_DC) * 100;
 
 OCR2B = ((OCR2A + 1) / toPWM_DC) - 1;
 //Serial.println("ALT GODT");
 }
 else {
 toPWM_DC = 0;
 
 OCR2B = ((OCR2A + 1) / toPWM_DC) - 1;
 }
 }
 /*
 void dc_motor_loop(){
 float error = Distanceref - Distancemeas;
  
 }
 */
 void magnet_detect() {
 tlast = tstart;
 tstart = millis();
 interruptCounter++;
 }


