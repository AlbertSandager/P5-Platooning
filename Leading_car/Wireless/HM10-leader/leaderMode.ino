void leaderMode() {

  //if mac address is received and the connection is ready. Send out the full message in followermode
  if (MacADDRbool == true) {
    //MacADDRCon = 'C';
    //confirmation = 'W';

<<<<<<< HEAD
      package.toCharArray(messageOut, package.length() + 1);
      transmitmsg();
      firstMessage = 0;
      Serial.println("First message sent");
    }

    digitalWrite(13, HIGH);
=======
    String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(MacADDRCon) + String(separator) + String(emergencyVal) + String(separator) + String(stopbit);

    package.toCharArray(messageOut, package.length() + 1);


    //main thing runs HERE!!!
    digitalWrite(13, HIGH);

    transmitmsg();
>>>>>>> parent of b25c5b7... lavet ting om
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
