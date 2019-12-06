//#include <TimerOne.h>
#include <Servo.h>
#define feedback_PIN A0
#define PWM_PIN 9

unsigned long t0 = 0;
const unsigned long ts = 5;

float T = 0.0005;
float PWM_OUT = 0;

int servocounter = 0;

unsigned long timeold = 0;
float Kp = 2;
float Kv = 2;

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
float realDistance = 0.30;
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

volatile int interruptCounter = 0;

// Timing
unsigned long tservoLast = 0;
unsigned long tDCLast = 0;
unsigned long tvelocityLast = 0;
unsigned long tDistanceLast = 0;

int lastSensorValue = 0;

int fServo = 400;
int fDC = 40;
int fvelocity = 10000;
int fDistance = 1000;

int distanceENABLE = 12;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  myservo.attach(10);


  t0 = millis();
  pinMode(distanceENABLE, OUTPUT);
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


  if((tservoLast + (1/float(fServo))*1000) < millis()) {

    servoLoop();

    //Serial.println("SERVO");

    tservoLast = millis(); // IMPORTANT
  }


  if((tDCLast + (1/float(fDC))*1000) < millis()) {

    distanceControl();

    //Serial.println("DC");



    tDCLast = millis(); // IMPORTANT
  }

  if((tvelocityLast + (1/float(fvelocity))*1000) < millis()) {

    calculateVelocity();

    //Serial.println("VELOCITY");



    tvelocityLast = millis(); // IMPORTANT
  }

  if((tDistanceLast + (1/float(fDistance))*1000) < millis()) {

    calculateDistance();
    //Serial.println("DISTANCE");




    tDistanceLast = millis(); // IMPORTANT
  }




}
float velocity = 0;
void calculateVelocity(){
  float interval = millis()-timeold;
  if(interruptCounter >= 2){
    float velocityTMP = ((circumference / magnets) / (interval / 1000));
    if(velocityTMP < 8) velocity = velocityTMP;
    timeold = millis();
    interruptCounter = 0;
    //Serial.println(velocity);
  }

}

void calculateDistance(){
  //digitalWrite(distanceENABLE,LOW);
  int sensorValue = analogRead(A1);
  if(sensorValue > lastSensorValue) {
    IRdistance = 187754 * pow(lastSensorValue+1, -1.51);
    lastSensorValue = lastSensorValue + 1;}
    
    
  else if(sensorValue < lastSensorValue) {
    IRdistance = 187754 * pow(lastSensorValue-1, -1.51);
    lastSensorValue = lastSensorValue - 1;}
    
  realDistance = IRdistance/100;
  digitalWrite(distanceENABLE,HIGH);
}

void servoLoop(){
  if (Serial.available()) {
    theta = Serial.read();
  }
  T = (1/float(fServo));
  Kp = Kp/velocity;
  float error = ref - theta;
  DUTY = (1-10*T)*lastduty+Kp*(0.1*T-1)*lasterror+Kp*error;
 /* Serial.print(ref);
   Serial.print(',');
   Serial.print(error);
   Serial.print(',');
   Serial.println(DUTY);*/
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
  DUTY = map(DUTY, 5*100, -5*100, 2500, 4000);
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
  //if(servocounter >= 2){
    //Serial.println(angle);
    myservo.write(angle);
    servocounter = 0;
  //}
  /*Serial.print(',');
   Serial.println(angle);*/
  //DUTY = 4.3; //remove this

  //toPWM = (1 / DUTY) * 100;

  //OCR1B = ((OCR1A + 1) / toPWM) - 1;
}

float PWM_DC = 0;
float PWM_last_DC = 0;
float PWM_real_DC = 0;
float Error_DC = 0;
float Error_last_DC = 0;
float V_last = 0;

void distanceControl(){
   //D_measured = output of distance meter.
  float V_measured;
  if(digitalRead(button) == LOW){
  float D_ref = 0.324; 
  float K_p_distance = -2;
  float K_i_distance = -0.3;
  float K_v_distance = 0.1;
  
  float D_measured = realDistance;
  velocity = velocity*100;
  
    V_measured = map(velocity,0,800,0,100);
    V_measured = V_measured/100;
    
    if(V_measured < 1 && V_measured > 0){
     V_last = V_measured; 
    }
    else V_measured = V_last;
  
  Error_DC = D_ref - D_measured;
  PWM_DC = ((Error_DC - Error_last_DC)*K_p_distance) + (K_i_distance*Error_last_DC*T) + PWM_last_DC;
  PWM_real_DC = PWM_DC - (K_v_distance * V_measured);

  //Sæt motor ting til PWMa
  
  Error_last_DC = Error_DC;
  PWM_last_DC = PWM_DC; // DUTY CYCLE
  
  
    
    if(PWM_real_DC > 1) PWM_real_DC = 1;
    else if(PWM_real_DC < 0) PWM_real_DC = 0;
    if(PWM_real_DC == 0)toPWM_DC = 0;
    else toPWM_DC = (1 / float(PWM_real_DC*100)) * 100;

  if(realDistance > 1) toPWM_DC = 0;
  
  OCR2B = ((OCR2A + 1) / toPWM_DC) - 1;
  
  Serial.print(realDistance);
  Serial.print(',');
  Serial.print(V_measured);
  Serial.print(',');
  Serial.print(toPWM_DC);
  Serial.print(',');
  Serial.print(PWM_DC);
  Serial.print(',');
  Serial.println(PWM_real_DC);
}


else {
    toPWM_DC = 0;

    OCR2B = ((OCR2A + 1) / toPWM_DC) - 1;
  }
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
  //tlast = tstart;
  //tstart = millis();
  interruptCounter++;
  //Serial.println("detect");
}



