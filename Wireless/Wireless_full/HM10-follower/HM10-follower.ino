#include <AltSoftSerial.h>
AltSoftSerial BTserial;
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html

unsigned long starttime;
unsigned long endtime;
int button = 7;
char c = ' ';
char transmit = 'G';
boolean NL = true;
int choker = 0;
char caseChoice = 'C';
char carStatus[30] = "gewh";
char ADDRcommand[8] = "AT+ADDR?"; //the command to fetch mac adress
char connectionStatus[50];
char platooningMode[15];
String MacADDRisolated;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  BTserial.begin(9600);
  Serial.println("BTserial started at 9600");
  delay(100);
}



//void func() {
//  if (transmit != 10 & transmit != 13 & choker == 0)
//  {
//    BTserial.write(transmit);  // transmit the predetermined character
//    starttime = micros();      // take the starttime of the transmission
//    choker = 1;
//  }
//  if (BTserial.available())
//  {
//    char receive = ' ';             // make an empty char to receive char
//    receive = BTserial.read();      // place the received char in the variable
//    if (receive == 'J') {           // if the received char is J
//      endtime = micros();          // stop the timer
//      unsigned long total = endtime - starttime; //calculate total transmission time
//      Serial.println("Total time is: ");
//      Serial.println(total);
//      receive = ' ';               // empty the char
//      delay(1000);
//      choker = 0;
//    }
//  }
//}

void loop()
{
  switch (caseChoice) {
    case 'C':
      delay(100);
      if (connectionStatus[0] == NULL)  {  //only send the message if our Mac adress is non-existant
        //Serial.print("ConnectionStatus = NULL");
        for (int k = 0; k < 100; k++)  { // do it 50 times just to be sure
          if (BTserial.available()) {
            connectionStatus[k] = BTserial.read(); //fill up the receiving array
            //Serial.print(connectionStatus[k]); //print the response from the HM-10
          }
        }
        String connectionStatusStr(connectionStatus); //convert char array to string
        //Serial.println(connectionStatusStr);
        char CSseperator = connectionStatusStr.indexOf('O');  //set up seperator
        String CSisolated = connectionStatusStr.substring(CSseperator, ' ');
        if (CSisolated == "OK+CONN")  {
          Serial.println("Connection established");
          caseChoice = 'M';
        }
      }
      break;
    case 'M':
      Serial.println("Choose platooning mode");
      Serial.println("1. Leader mode");
      Serial.println("2. Follower mode");
      while (platooningMode[0] == NULL)  {
        if (Serial.available() > 0) {
          char tempCasechoice = Serial.read();
          Serial.println(tempCasechoice);
          if (tempCasechoice != '1' || tempCasechoice != '2' & tempCasechoice != NULL) {
            Serial.println("Your choice is invalid");
          }
          delay(30);
          if (tempCasechoice == '1')  {
            caseChoice = tempCasechoice;
            Serial.println("caseChoice = tempCasechoice = 1");
            platooningMode[0] = "Leader";
          }
          delay(30);
          if (tempCasechoice == '2')  {
            caseChoice = tempCasechoice;
            Serial.println("caseChoice = tempCasechoice = 2");
            platooningMode[0] = "Follower";
          }
          delay(30);
        }
      }
      break;
    case '1':
      //Serial.println("You have chosen leader mode");
      leaderMode();
      break;
    case '2':
      //Serial.println("You have chosen leader mode");
      //followerMode();
      break;
    case '3':
      Serial.println("CASE 3 MOTHERFUCKER");
      while (1)  {
        //do nothing
      }
      break;
  }
}



//    if (digitalRead(button) == LOW)  {
//      func();
//    }
/*
  // Read from the Bluetooth module and send to the Arduino Serial Monitor
  if (BTserial.available())
  {
   c = BTserial.read();
   Serial.write(c);
  }


  // Read from the Serial Monitor and send to the Bluetooth module
  if (Serial.available())
  {
   c = Serial.read();
   // do not send line end characters to the HM-10
   if (c!=10 & c!=13 )
   {
        BTserial.write(c);
   }

   // Echo the user input to the main window.
   // If there is a new line print the ">" character.
   if (NL) { Serial.print("\r\n>");  NL = false; }
   Serial.write(c);
   if (c==10) { NL = true; }
  }
*/
