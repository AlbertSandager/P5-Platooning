//sending message
void sendmsg() {
  String msg = String(startbyte) + String(address) + String(seperator) + String(addressCon) + String(seperator) + String(emergencyVal) + String(stopbyte);
  mySerial.print(msg);
  //Serial.println("Following information sent:");
  //Serial.println(msg);
  //Send "tal" with the RF-module.
  //Serial.println(""); Serial.print("String sent to next car: "); Serial.print(msg); Serial.println(""); //Serial print for debugging
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
  char seperatorEt = A.indexOf(seperator);
  char seperatorTo = A.indexOf(seperator, seperatorEt + 1);
  char seperatorTre = A.indexOf(stopbyte);
  addressRec = A.substring(startSeperator, seperatorEt);
  addressConRec = A.substring(seperatorEt + 1, seperatorTo);
  emergencyValRec = A.substring(seperatorTo + 1, seperatorTre);
  
  if (addressRecOld != " ") {
    addressCon = 'M';
  }
  if (addressRecOld == addressRec) {
    addressCon = 'R';
  }
  else if (addressRecOld != addressRec && addressRecOld != " ") {
    addressCon = 'W';
  }
  if (emergencyValRec == "Y" && addressCon == 'W' || addressCon == 'M') {
    emergencyVal = 'D';
  }
  if (emergencyValRec == "N") {
    emergencyVal = 'I';
  }
  if (emergencyValRec == "Y" && addressRecOld == addressRec)  {
    emergencyVal = 'C';
  }
  if (addressRecOld == " ") {
  addressRecOld = addressRec;
  }
  
  listening = false;

}