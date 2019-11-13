//  SerialIn_SerialOut_HM-10_01
//
//  Uses hardware serial to talk to the host computer and AltSoftSerial for communication with the bluetooth module
//
//  What ever is entered in the serial monitor is sent to the connected device
//  Anything received from the connected device is copied to the serial monitor
//  Does not send line endings to the HM-10
//
//  Pins
//  BT VCC to Arduino 5V out.
//  BT GND to GND
//  Arduino D8 (SS RX) - BT TX no need voltage divider
//  Arduino D9 (SS TX) - BT RX through a voltage divider (5v to 3.3v)
//

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
char caseChoice = '0';
char carStatus[30] = "gewh";
char MacADDR[50];

void setup()
{
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  BTserial.begin(9600);
  Serial.println("BTserial started at 9600");
}



void func() {
  if (transmit != 10 & transmit != 13 & choker == 0)
  {
    BTserial.write(transmit);  // transmit the predetermined character
    starttime = micros();      // take the starttime of the transmission
    choker = 1;
  }
  if (BTserial.available())
  {
    char receive = ' ';             // make an empty char to receive char
    receive = BTserial.read();      // place the received char in the variable
    if (receive == 'J') {           // if the received char is J
      endtime = micros();          // stop the timer
      unsigned long total = endtime - starttime; //calculate total transmission time
      Serial.println("Total time is: ");
      Serial.println(total);
      receive = ' ';               // empty the char
      delay(1000);
      choker = 0;
    }
  }
}

void loop()
{
  switch (caseChoice) {
    case '0':
      Serial.print("Bluetooth setup has started");




      
      break;
    case '1':
      Serial.println("Choose platooning mode");
      Serial.println("1. Leader mode");
      Serial.println("2. Follower mode");
      while (caseChoice == '0') {
        if (Serial.available() > 0) {
          caseChoice = Serial.read();
        }
      }
      break;
    case '2':
      //Serial.println("You have chosen leader mode");
      leaderMode();
      break;
    case '3':
      //Serial.println("You have chosen leader mode");
      followerMode();
      break;
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
}
