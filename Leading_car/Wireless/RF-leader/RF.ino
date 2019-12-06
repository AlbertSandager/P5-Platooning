//sending message
void sendmsg() {
  String msg = String(startbyte) + String(address) + String(seperator) + String(addressCon) + String(seperator) + String(emergencyVal) + String(stopbyte);
  mySerial.print(msg);                              //Send "tal" with the RF-module.
  // Serial.println("Sent: ");
  // Serial.print(msg);
  // Serial.println();

  mySerial.flush();
}

//receiveing message
void receivemsg() {
  listening = true;
  if (mySerial.available() > 0 )
  {
    mySerial.readBytesUntil(stopbyte, instring, NRCHAR); //break character = /
    mySerial.flush();
    String str = String(instring);
    // Serial.println("Received: ");
    // Serial.println(str);
    char startChar = str.charAt(0);                //Check the first character in the array
    if (startChar == startbyte) {                        //If the start-character is correct, proceed to analyze the data.
      splitUp(str);                                //split up the received string
    }
  }
}


//splitting message up
void splitUp(String A ) //Function for splitting up the received string. Using seperators, it makes 3 substrings and converts them to ints.
{

  char startSeperator = A.indexOf(startbyte) + 1; //finding the startbyte
  char seperatorOne = A.indexOf(seperator); //finding first seperator
  char seperatorTwo = A.indexOf(seperator, seperatorOne + 1); //finding second seperator
  char seperatorThree = A.indexOf(stopbyte); //finding stopbyte
  addressRec = A.substring(startSeperator, seperatorOne); //reading everything between the startbyte and the first seperator
  addressConRec = A.substring(seperatorOne + 1, seperatorTwo); //reading everything between the first seperator and the second seperator
  emergencyValRec = A.substring(seperatorTwo + 1, seperatorThree); //reading everything between the second seperator and the stopbyte

  if (addressRecOld != " ") {
    addressCon = 'M';
  }
  if (addressRecOld == addressRec) {
    addressCon = 'R';
  }
  else if (addressRecOld != addressRec && addressRecOld != " ") {
    addressCon = 'W';
  }
  if (digitalRead(6) == LOW)  {
    emergencyVal = 'Y';
  }
  else {
    emergencyVal = 'N';
  }
  if (digitalRead(7) == LOW) {
    address = "HCY5RR4N68KT"; // 1 character changed
  }
  else {
    address = "HCY5RR4N68KW";
  }


  listening = false;

}
