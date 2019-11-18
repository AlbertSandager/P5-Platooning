#include <AltSoftSerial.h>
AltSoftSerial BTserial;
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html

//Global variables

//unsigned long starttime;
//unsigned long endtime;
//int button = 7;
//char c = ' ';
//char transmit = 'G';
//boolean NL = true;
//int choker = 0;
char caseChoice = 'C';    // choice of case in switch case
char carStatus[30] = "gewh";
char ADDRcommand[8] = "AT+ADDR?"; //the command to fetch mac adress
char connectionStatus[50];
char tempMacADDR[15]; // array for mac adress
int MacADDRcontrolInt = 0;
bool MacADDRbool = false;
bool connectionbool = false;
char messageOut[30];  
int packageLen;
char ATcommand[8] = "AT+RESET";
int ATcntrlVar = 0;
int WHILEcntrl = 0;
String CSisolated;



//Variables for communication
char separator = ':';
char startbit = 'P'; // P
String MacADDR;   // Mac adress of HM-10
char platooningMode = NULL;  // L = leader     F = follower
char wantedStatus = ' ';  // L = leader    // F = follower
char confirmation = ' '; // G = good to go = confirmed     // D = denied    // W = waiting for request
char STOPstatus = ' ';     // C = continue     S = STOP
char stopbit = 'Q';  // Q




void setup()
{
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  BTserial.begin(9600);
  Serial.println("BTserial started at 9600");
  delay(100);
}



void loop()
{
  switch (caseChoice) {
    case 'C':
      connectionControl();  //test the connection to the other car. If the connection is good, proceed to case M
      break;
    case 'M':
      Serial.println("Choose platooning mode");
      Serial.println("1. Leader mode");
      Serial.println("2. Follower mode");
      while (platooningMode == NULL)  {
        if (Serial.available() > 0) {
          char tempCasechoice = Serial.read();
          Serial.println(tempCasechoice);
          if (tempCasechoice != '1' && tempCasechoice != '2') {  //  & tempCasechoice != NULL
            Serial.println("Your choice is invalid");
          }
          delay(30);
          if (tempCasechoice == '1')  {
            caseChoice = tempCasechoice;
            Serial.println("Leader mode has been chosen");
            platooningMode = 'L'; //l for leader
            Serial.println("Fetching Mac-address...");
            caseChoice = '1';
          }
          delay(30);
          if (tempCasechoice == '2')  {
            caseChoice = tempCasechoice;
            Serial.println("Follower mode has been chosen");
            platooningMode = 'F'; //f for follower
            Serial.println("Fetching Mac-address...");
            caseChoice = '2';
          }
          delay(30);
        }
      }
      break;
    case '1':
      MacADDRcontrol();
      if (MacADDRbool == true)  {
        leaderMode();
      }
      
      break;
    case '2':
      MacADDRcontrol();
      if (MacADDRbool == true)  {
        followerMode();
      }
      break;
    case '3':
      Serial.println("CASE 3 MOTHERFUCKER");
      delay(1000);
      break;
  }
}
