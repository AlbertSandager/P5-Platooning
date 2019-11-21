volatile byte magnet_counter  = 0;
float velocity = 0.0;
unsigned int rpm = 0;
unsigned long timeold = 0;
unsigned long starttime = 0;
int period = 25; //100 ms
unsigned long time_last = 0;
double circumference = 0.2765; //27,65 cm
double magnets = 4.0;
//double result = 0;
int pwm = 11; // assigns pin 12 to variable pwm
int speeddelay = 50;
unsigned long LOWcounter = 0;
unsigned long total_time = 0;


void setup() {
  Serial.begin(9600);
  //attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
  pinMode(pwm, OUTPUT); // declares pin 12 as output
  pinMode(6, OUTPUT);  // declares pin A0 as input
  pinMode(7, OUTPUT);  // declares pin A0 as input
  pinMode(5, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  if (millis() > time_last + period)  {
    if (digitalRead(2) == HIGH)  {
      LOWcounter++;
    } else if (digitalRead(2) == LOW) {
      total_time = LOWcounter * period; //eks 200 ms
//      Serial.print("Circumference/magnets = ");
//      Serial.println((circumference/magnets),6);
//      Serial.print("total time is");
//      Serial.println(total_time);
//      Serial.print("total time * 0,1 = ");
//      Serial.println((total_time*0.1),4);  
      velocity = ((circumference/magnets)/(total_time*0.1))*3.6; //how much time it took to reach a magnet/HIGH
      time_last = millis();
      Serial.println(velocity, 8);
      LOWcounter = 0;
    }
    //velocity = ((magnet_counter * (circumference / magnets)) * 10.0) * 3.6;

    //time_last = millis();
    //magnet_counter = 0;
  }

  if (digitalRead(5) == LOW) {
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(pwm, HIGH); // sets pin 12 HIGH
    delayMicroseconds(speeddelay);   // waits for t1 uS (high time)
    digitalWrite(pwm, LOW);  // sets pin 12 LOW
    delayMicroseconds(speeddelay);   // waits for t2 uS (low time)
  }
  //Measure RPM
  //    if (magnet_counter >= 20) {
  //      rpm = 30 * 1000 / (millis() - timeold) * magnet_counter;
  //      timeold = millis();
  //      magnet_counter = 0;
  //      Serial.println(rpm,DEC);
  //    }


}

void magnet_detect() {
  //This function is called whenever a magnet/interrupt is detected by the arduino
  magnet_counter++;

}
