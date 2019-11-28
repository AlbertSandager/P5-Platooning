#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12);
unsigned long starttime;
unsigned long endtime;
int button = 7;
int wiredInput = 12;
boolean NL = true;
int choker = 0;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  pinMode(wiredInput, INPUT);
  Serial.begin(115200);
  Serial.flush();
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.flush();
}


void loop()
{
  if (choker == 0 && digitalRead(button) == HIGH)
  {
    Serial.println("Im already in here");
    String out = String('G');
    mySerial.print(out);    // sender det der blev skrevet i serial monitor over RF
    mySerial.flush();
    starttime = micros();      // take the starttime of the transmission
    choker = 1;
  }
  
  if (digitalRead(wiredInput) == HIGH)  {
    Serial.println("Total 1-way time is: ");
    endtime = micros();                         // stop the timer
    unsigned long total = endtime - starttime;  //calculate total transmission time
    Serial.println(total);
    delay(1000);
    choker = 0;
  }
}
