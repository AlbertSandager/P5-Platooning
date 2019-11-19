volatile byte half_revolutions  = 0;
unsigned int rpm = 0;
unsigned long timeold = 0;

void setup() {
  
  Serial.begin(9600);
  attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
}

void loop() {

  //Measure RPM
  if (half_revolutions >= 20) {
    rpm = 30 * 1000 / (millis() - timeold) * half_revolutions;
    timeold = millis();
    half_revolutions = 0;
    Serial.println(rpm,DEC);
  }
}

void magnet_detect() {

  //This function is called whenever a magnet/interrupt is detected by the arduino
  half_revolutions++;
  Serial.println("detect");
}
