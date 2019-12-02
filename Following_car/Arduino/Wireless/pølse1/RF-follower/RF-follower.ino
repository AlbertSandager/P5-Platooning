#include <SoftwareSerial.h>
#include <AES.h>

#define NRCHAR 20
#define OUTCHAR 100

SoftwareSerial mySerial(11, 12); // RX, TX
AES aes ;

char instring[NRCHAR]; //array for received data.


//Variables for sending
char startbyte = '/'; // Startbyte for the message
char seperator = ':'; // Seperator for the message
String address = "V5WBFS4H03X0"; // Mac adress of RF module
char addressCon = ' '; // Confirmation that the MAC-address has been received
char emergencyVal = ' '; // Emergency stop C for confirmed D for denied and I for no request
char stopbyte = '&'; // Stopbyte for the message
String encryptMsgout;


//Variables for receiveing
String addressRec = " ";
String addressRecOld = " ";
String addressConRec;
String emergencyValRec;
bool listening = true;
bool startchatting = true;
byte encryptMsgin[48];
String decryptMsgin;


//varibles for encryption
unsigned int keyLength [3] = {128, 192, 256}; // key length: 128b, 192b or 256b
 
byte *key = (unsigned char*)"01234567890123456789012345678901"; // encryption key
byte plain[] = "abcdefghijkl"; // plaintext to encrypt
 
unsigned long long int myIv = 36753562; // CBC initialization vector; real iv = iv x2 ex: 01234567 = 0123456701234567


void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.flush();

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.flush();
}

void loop() {

  //listening for message
  receivemsg();

  //if message is received then run the sending
  if (listening == false) {
    sendmsg();
  }

 

  //printing received values
//  Serial.println(addressRec);
//  Serial.println(addressConRec);
//  Serial.println(emergencyValRec);

}
