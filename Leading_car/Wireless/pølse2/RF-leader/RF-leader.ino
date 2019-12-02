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
String address = "HCY5RR4N68KW"; // Mac adress of RF module
char addressCon = 'M'; // Confirmation that the MAC-address has been received
char emergencyVal = 'N'; // Emergency stop N for no Y for yes
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
