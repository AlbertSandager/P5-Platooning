#include <SoftwareSerial.h>

#define NRCHAR 20
#define OUTCHAR 100

SoftwareSerial mySerial(11, 12); // RX, TX


char instring[NRCHAR]; //array for received data.


//Variables for sending
char startbyte = '/'; // Startbyte for the message
char seperator = ':'; // Seperator for the message
String address = "V5WBFS4H03X0"; // Mac adress of RF module
char addressCon = ' '; // Confirmation that the MAC-address has been received
char emergencyVal = ' '; // Emergency stop C for confirmed D for denied and I for no request
char stopbyte = '&'; // Stopbyte for the message


//Variables for receiveing
String addressRecOld = " ";
String addressRec;
String addressConRec;
String emergencyValRec;
bool listening = true;

unsigned long tStart;
unsigned long tStop;

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.flush();

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.flush();

  pinMode(4, INPUT_PULLUP); //pin for emergency stop button (for getting out of emergency stop)
}

void loop() {

  //listening for message
  receivemsg();
  
tStop=micros();

if((tStop-tStart)>116700){
  Serial.println((tStop-tStart));
  Serial.println("Stopping car!");
}

}
