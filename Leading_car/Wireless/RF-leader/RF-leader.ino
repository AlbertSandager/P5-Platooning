#include <SoftwareSerial.h>

#define NRCHAR 20
#define OUTCHAR 100

SoftwareSerial mySerial(11, 12); // RX, TX


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

sendmsg(5, 6, 7);
}
