int wiredOutput = 7;
char receiveVal;

void setup()
{
  pinMode(wiredOutput, OUTPUT);
  Serial.begin(115200);
  Serial.flush();
  // set the data rate for the SoftwareSerial port
  Serial3.begin(9600);
  Serial3.flush();
}

void loop()
{
  if (Serial3.available())
  {
    receiveVal = Serial3.read();
    if (receiveVal == 'G') {
      digitalWrite(wiredOutput, HIGH);
      delay(500);
      digitalWrite(wiredOutput, LOW);
    }
    else digitalWrite(wiredOutput, LOW);
  }
}
