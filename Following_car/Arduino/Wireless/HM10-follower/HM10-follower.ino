#include <AltSoftSerial.h>
AltSoftSerial BTserial;
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html


//Global variables
char caseChoice = '1';    // choice of case in switch case

//variables for connectioncontrol
char ADDRcommand[8] = "AT+ADDR?"; //the command to fetch mac adress
char tempMacADDR[25]; // array for mac adress
int MacADDRcontrolInt = 0;
bool MacADDRbool = false;
int WHILEcntrl = 0;

int firstMessage = 1; //always 1 at start since we dont have any message received

//variables for messaging
char messageOut[20];
char messageIn[20];
String MacADDRRec = " ";   // Mac adress of HM-10
String MacADDRConRec = " ";   // Mac adress of HM-10
String emergencyValRec = " ";
String stopbitRec = " ";
String startbitRec = " ";
String separatorRec = " ";

//Variables for communication
char separator = ':';
char startbit = '/'; // /
String MacADDR = " ";   // Mac adress of HM-10
char MacADDRCon = ' ';
char emergencyVal = ' '; // N for no Y for yes
char stopbit = '&';  // &


void setup() {
  Serial.begin(115200);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  BTserial.begin(9600);
  Serial.println("BTserial started at 115200");
  delay(100);
}


void loop() {
<<<<<<< HEAD
  MacADDRcontrol();
  while (MacADDRbool == true)  {
    followerMode();
=======

  switch (caseChoice) {
    case 'C':
      //connectionControl();  //test the connection to the other car. If the connection is good, proceed to case M
      break;

    case 'M':
      Serial.println("Choose platooning mode");
      Serial.println("1. Leader mode");
      Serial.println("2. Follower mode");
      while (caseChoice == 'M')  {
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
            Serial.println("Fetching Mac-address...");
          }
          delay(30);
          if (tempCasechoice == '2')  {
            caseChoice = tempCasechoice;
            Serial.println("Follower mode has been chosen");
            Serial.println("Fetching Mac-address...");
          }
        }
      }
      break;

    case '1':
      Serial.println("Running in leading mode mode");
      break;

    case '2':
      MacADDRcontrol();
      //while (MacADDRbool == true)  {
        followerMode();
      //}
      break;
>>>>>>> parent of cba6e97... det hele sejler :(((((
  }
}
