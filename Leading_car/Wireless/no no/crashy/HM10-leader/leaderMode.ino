void leaderMode() {

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

    //sending emergency break to follower
    if (digitalRead(4) == LOW) {
      emergencyVal = 'Y';
    }
    else {
      emergencyVal = 'N';
    }

  }
