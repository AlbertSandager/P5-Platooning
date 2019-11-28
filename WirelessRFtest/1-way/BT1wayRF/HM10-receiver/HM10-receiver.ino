#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12); // RX, TX
int wiredOutput = 7;
char receive;

void setup()
{
  pinMode(wiredOutput, OUTPUT);
  Serial.begin(115200);
  Serial.flush();
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.flush();
}

void loop()
{
  if (mySerial.available())
  {
    receive = mySerial.read();
    if (receive == 'G') {
      digitalWrite(wiredOutput, HIGH);
      delay(500);
      digitalWrite(wiredOutput, LOW);
    }
  }
}
