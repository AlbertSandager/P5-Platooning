#include <TimerOne.h>
#define PWM_PIN 10
//volatile byte magnet_counter  = 0;
float velocity = 0.0;
//unsigned int rpm = 0;
//unsigned long timeold = 0;
int period = 10; //100 mu-s
unsigned long time_last = 0;
double circumference = 0.2765; //27,65 cm
double magnets = 4.0;
unsigned long LOWcounter = 0;
unsigned long total_time = 0;
int last_magnetstate = 0;
unsigned long timer = 0;
unsigned long newmillis = 0;
int magnet_status_old = 0;
int magnet_status_new = 0;


void setup() {
  Timer1.initialize(2000);
  Timer1.pwm(PWM_PIN, 128, 20);
  Serial.begin(9600);
  //attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
  pinMode(PWM_PIN, OUTPUT); // declares pin 12 as output
  pinMode(6, OUTPUT);  // declares pin A0 as input
  pinMode(7, OUTPUT);  // declares pin A0 as input
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  pinMode(2, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(2) == LOW && last_magnetstate == 0)  {
    timer = micros();
    if  (magnet_status_new +1 == magnet_status_old)  {
      newmillis = micros();
      total_time = newmillis - timer;
      velocity = ((circumference / magnets) / ((total_time) * (1 / 1000))) * 3.6;
      Serial.println(total_time);
      magnet_status_new++;
    }
    magnet_status_old++;
    LOWcounter++;
    last_magnetstate = 1;
  }
  else if (digitalRead(2) == HIGH && last_magnetstate == 1)  {
    last_magnetstate = 0;
  }



  //  if (micros() > time_last + period)  {
  //    if (digitalRead(2) == HIGH)  {
  //      LOWcounter++;
  //      time_last = micros();
  //      last_magnetstate = 0;
  //    } else if (digitalRead(2) == LOW && last_magnetstate == 0) {
  //
  //      total_time = LOWcounter * period * 1/(10^6); //* (1/1000); //eks 200 ms
  //      //      Serial.print("Circumference/magnets = ");
  //      //      Serial.println((circumference/magnets),6);
  //      //      Serial.print("total time is");
  //      //      Serial.println(total_time);
  //      //      Serial.print("total time * 0,1 = ");
  //      //      Serial.println((total_time*0.1),4);
  //      velocity = ((circumference / magnets) / (total_time)) * 3.6; //how much time it took to reach a magnet/HIGH
  //      time_last = micros();
  //      Serial.println(velocity, 12);
  //      LOWcounter = 0;
  //      last_magnetstate = 1;
  //    }
  //  }


  if (digitalRead(5) == LOW) {
    Timer1.setPwmDuty(PWM_PIN, 128);
  } else if (digitalRead(5) == HIGH)  {
    Timer1.setPwmDuty(PWM_PIN, 0);
  }
  //Measure RPM
  //    if (magnet_counter >= 20) {
  //      rpm = 30 * 1000 / (millis() - timeold) * magnet_counter;
  //      timeold = millis();
  //      magnet_counter = 0;
  //      Serial.println(rpm,DEC);
  //    }
}

//void magnet_detect() {
//  //This function is called whenever a magnet/interrupt is detected by the arduino
//  magnet_counter++;
//}
