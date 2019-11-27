void leaderMode() {

  //if mac address is received and the connection is ready. Send out the full message in followermode
  if (MacADDRbool == true) {
    if (firstMessage) {
      char MacADDRCon = 'M';
      char emergencyVal = 'N';
      String package = String (startbit) + String(separator) +
                       String(MacADDR) + String(separator) + String(MacADDRCon) +
                       String(separator) + String(emergencyVal) + String(separator) + String(stopbit);

      package.toCharArray(messageOut, package.length() + 1);
      transmitmsg();
      firstMessage = 0;
      Serial.println("First message sent");
    }

    digitalWrite(13, HIGH);
    receivemsg();

    //Serial.println(MacADDRRec);
    //Serial.println(MacADDRConRec);
    //Serial.println(emergencyValRec);

    //MacADDRCon = 'C';


  }

  else {
    Serial.print("Mac-address not fetched or connection not available");
    //caseChoice = 'M';
  }
}

void analyze()  {
  
}
