#include <SoftwareSerial.h>

#define NRCHAR 20
#define OUTCHAR 100

SoftwareSerial mySerial(11, 12); // RX, TX


char instring[NRCHAR]; //array for received data.


//Variables for sending
char startbyte = '/';
char seperator = ':';
String address = "V5WBFS4H03X0";   // Mac adress of HM-10
char addressCon = 'C';   // Mac adress of HM-10
char emergencyVal = 'D'; // N for no Y for yes
char stopbyte = '&';


//Variables for receiveing
String addressRec;
String addressConRec;
String emergencyValRec;
bool listening = true;



void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.flush();

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.flush();
}

void loop() {

  receivemsg();

  if (listening == false) {
    sendmsg();
  }

  Serial.println(addressRec);
  Serial.println(addressConRec);
  Serial.println(emergencyVal);

}
