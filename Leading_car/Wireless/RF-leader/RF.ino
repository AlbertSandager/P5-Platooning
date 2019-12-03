//sending message
void sendmsg() {
  String msg = String(startbyte) + String(address) + String(seperator) + String(addressCon) + String(seperator) + String(emergencyVal) + String(stopbyte);
  mySerial.print(msg);                              //Send "tal" with the RF-module.
  //  Serial.println("Following information sent:");
  //  Serial.println(msg);
  //  Serial.println(""); Serial.print("String sent to next car: "); Serial.print(msg); Serial.println(""); //Serial print for debugging
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
    Serial.println("Following information received:");
    Serial.println(str);
    Serial.println();
    char startChar = str.charAt(0);                //Check the first character in the array
    if (startChar == startbyte) {                        //If the start-character is correct, proceed to analyze the data.
      splitUp(str);                                //split up the received string
    }
  }
}


//splitting message up
void splitUp(String A ) //Function for splitting up the received string. Using seperators, it makes 3 substrings and converts them to ints.
{

  char startSeperator = A.indexOf(startbyte) + 1;
  char seperatorOne = A.indexOf(seperator);
  char seperatorTwo = A.indexOf(seperator, seperatorOne + 1);
  char seperatorThree = A.indexOf(stopbyte);
  addressRec = A.substring(startSeperator, seperatorOne);
  addressConRec = A.substring(seperatorOne + 1, seperatorTwo);
  emergencyValRec = A.substring(seperatorTwo + 1, seperatorThree);

  if (addressRecOld != " ") {
    addressCon = 'M';
  }
  if (addressRecOld == addressRec) {
    addressCon = 'R';
  }
  else if (addressRecOld != addressRec && addressRecOld != " ") {
    addressCon = 'W';
  }
  if (digitalRead(4) == LOW)  {
    emergencyVal = 'Y';
  }
  else {
    emergencyVal = 'N';
  }
  if (digitalRead(8) == LOW) {
    address = "HCY5RR4N68KT"; // 1 character changed
  }
  else {
    address = "HCY5RR4N68KW";
  }


  listening = false;

}
