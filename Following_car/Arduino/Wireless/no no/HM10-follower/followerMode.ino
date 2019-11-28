void followerMode() {
  //if mac address is received and the connection is ready. Send out the full message in followermode
  if (MacADDRbool == true) {
    //MacADDRCon = 'C';
    //confirmation = 'W';

    String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(MacADDRCon) + String(separator) + String(emergencyVal) + String(separator) + String(stopbit);

    package.toCharArray(messageOut, package.length() + 1);


    //main thing runs HERE!!!
    digitalWrite(13, HIGH);

    transmitmsg();
    receivemsg();

    Serial.println(MacADDRRec);
    Serial.println(MacADDRConRec);
    Serial.println(emergencyValRec);

    if (MacADDRRec.length() == 12) {
      MacADDRCon = 'R';
    }
    else {
      MacADDRCon = 'W';
    }


  }

  else {
    Serial.println("Mac-address not fetched or connection not available");
    Serial.println("Please restart");
    while (1)  {
      // do nothing
    }
  }
}
