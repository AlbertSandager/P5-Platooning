#include <Wire.h>
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
  Serial.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(30000);
  Serial.flush();
}


void loop()
{
  if (choker == 0)
  {
    String out = String('G');
    Serial.print(out);    // sender det der blev skrevet i serial monitor over RF
    Serial.flush();
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
