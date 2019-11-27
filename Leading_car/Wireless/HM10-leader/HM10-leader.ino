#include <AltSoftSerial.h>
AltSoftSerial BTserial;
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html


//Global variables
char caseChoice = 'C';    // choice of case in switch case
int statusChange = 0;

//variables for connectioncontrol
char ADDRcommand[8] = "AT+ADDR?"; //the command to fetch mac adress
char OKRESET[8];
char OKLOST[7];
char OKCONN[7];
char ATcommand[8] = "AT+RESET";
char tempMacADDR[25]; // array for mac adress
int MacADDRcontrolInt = 0;
bool MacADDRbool = false;
bool connectionbool = false;
int ATcntrlVar = 0;
int WHILEcntrl = 0;
String CSisolated;

//variables for messaging
char messageOut[24];
char messageIn[24];
String MacADDRRec;   // Mac adress of HM-10
String emergencyValRec;
String confirmationRec; // G = good to go = confirmed     // D = denied    // W = waiting for request
String stopbitRec;
String startbitRec;
String separatorRec;

//Variables for communication
char separator = ':';
char startbit = '/'; // /
String MacADDR;   // Mac adress of HM-10
char emergencyVal = ' '; // N for no Y for yes
char confirmation = ' '; // G = good to go = confirmed     // D = denied    // W = waiting for request
char stopbit = '&';  // &



void setup() {

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(115200);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  BTserial.begin(9600);
  Serial.println("BTserial started at 115200");
  delay(100);
}



void loop() {

  switch (caseChoice) {
    case 'C':
      connectionControl();  //test the connection to the other car. If the connection is good, proceed to case M
<<<<<<< HEAD
=======
      break;

    case 'M':
      Serial.println("Leader mode has been chosen");
      Serial.println("Fetching Mac-address...");
      caseChoice = '1';
>>>>>>> parent of b25c5b7... lavet ting om
      break;

    case '1':
      MacADDRcontrol();
      if (MacADDRbool == true)  {
        leaderMode();
      }
      break;
  }
}
