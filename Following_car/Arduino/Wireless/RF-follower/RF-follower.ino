#include <SoftwareSerial.h>

#define NRCHAR 20
#define OUTCHAR 100

SoftwareSerial mySerial(11, 12); // RX, TX

int val1;
int val2;
int val3;

char instring[NRCHAR]; //array for received data. 


void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
    Serial.flush();

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
    mySerial.flush();
}

void loop() // run over and over
{
receivemsg();
Serial.println(val1);
Serial.println(val2);
Serial.println(val3);
}
