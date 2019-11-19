#include <AltSoftSerial.h>
AltSoftSerial BTserial;
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html


//Global variables
char caseChoice = 'C';    // choice of case in switch case
char ADDRcommand[8] = "AT+ADDR?"; //the command to fetch mac adress
char OKRESET[8];
char OKLOST[7];
char OKCONN[7];
char ATcommand[8] = "AT+RESET";
char tempMacADDR[25]; // array for mac adress
int MacADDRcontrolInt = 0;
bool MacADDRbool = false;
bool connectionbool = false;


char messageOut[24];
char messageIn[24];

//received stuff
String MacADDRRec;   // Mac adress of HM-10
String platooningModeRec;  // L = leader     F = follower
String wantedStatusRec;  // L = leader    // F = follower
String confirmationRec; // G = good to go = confirmed     // D = denied    // W = waiting for request
String STOPstatusRec;     // C = continue     S = STOP
String stopbitRec;
String startbitRec;
String separatorRec;


int ATcntrlVar = 0;
int WHILEcntrl = 0;
String CSisolated;
int statusChange = 0;



//Variables for communication
char separator = ':';
char startbit = '/'; // P
String MacADDR;   // Mac adress of HM-10
char platooningMode = NULL;  // L = leader     F = follower
char wantedStatus = ' ';  // L = leader    // F = follower
char confirmation = ' '; // G = good to go = confirmed     // D = denied    // W = waiting for request
char STOPstatus = ' ';     // C = continue     S = STOP
char stopbit = '&';  // Q




void setup() {

  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  BTserial.begin(9600);
  Serial.println("BTserial started at 9600");
  delay(100);
}



void loop() {

  switch (caseChoice) {
    case 'C':
      connectionControl();  //test the connection to the other car. If the connection is good, proceed to case M
      break;

    case 'M':
      Serial.println("Leader mode has been chosen");
      platooningMode = 'L'; //l for leader
      Serial.println("Fetching Mac-address...");
      caseChoice = '1';
      delay(30);
      break;

    case '1':
      MacADDRcontrol();
      if (MacADDRbool == true)  {
        leaderMode();
      }
      break;
  }
}
