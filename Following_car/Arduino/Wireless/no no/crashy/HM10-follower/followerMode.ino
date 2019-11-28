void followerMode() {


  String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(MacADDRCon) + String(separator) + String(emergencyVal) + String(separator) + String(stopbit);

  package.toCharArray(messageOut, package.length() + 1);


  //main thing runs HERE!!!
  digitalWrite(13, HIGH);

  transmitmsg();
  receivemsg();

  Serial.println(MacADDRRec);
  Serial.println(MacADDRConRec);
  Serial.println(emergencyValRec);

  //Checking if the MACaddress is right or wrong
  if (MacADDRRec.length() == 12) {
    MacADDRCon = 'R';
  }
  else {
    MacADDRCon = 'W';
  }


  //Checking for emergency break from leader
  if (emergencyValRec == ' ') {
    emergencyVal = 'I';
  }
  if (emergencyValRec == 'Y') {
    emergencyVal = 'C';
  }
  else {
    emergencyVal = 'D';
  }


}
