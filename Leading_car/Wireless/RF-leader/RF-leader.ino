#include <SoftwareSerial.h>

#define NRCHAR 20
#define OUTCHAR 100

SoftwareSerial mySerial(11, 12); // RX, TX


char instring[NRCHAR]; //array for received data.


//Variables for sending
char startbyte = '/'; // Startbyte for the message
char seperator = ':'; // Seperator for the message
String address = "HCY5RR4N68KW"; // Mac adress of RF module
char addressCon = 'M'; // Confirmation that the MAC-address has been received
char emergencyVal = 'N'; // Emergency stop N for no Y for yes
char stopbyte = '&'; // Stopbyte for the message


//Variables for receiveing
String addressRec = " ";
String addressRecOld = " ";
String addressConRec;
String emergencyValRec;
bool listening = true;
bool startchatting = true;


void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.flush();
  pinMode(4, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.flush();
}

void loop() {

  //sending first message to start the boldkast
  if (startchatting == true) {
    sendmsg();
    startchatting = false;
  }

  //listening for message
  receivemsg();

  //if message is received then run the sending
  if (listening == false) {
    sendmsg();
  }

  if (addressRec != " " && addressRec.length() == 12) {
    addressCon = 'R';
  }

  //printing received values
//  Serial.println(addressRec);
//  Serial.println(addressConRec);
//  Serial.println(emergencyVal);

}
