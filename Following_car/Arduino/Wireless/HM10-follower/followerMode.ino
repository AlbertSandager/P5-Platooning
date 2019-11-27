void followerMode() {
  //if mac address is received and the connection is ready. Send out the full message in followermode
  if (MacADDRbool == true) {
<<<<<<< HEAD
    Serial.println("first message is being received now");
    receivemsg();
    Serial.println("Receivemsg has been run");
    if (firstMessage && MacADDRRec != " ") {
      MacADDRCon = 'R'; // yeah, we received your mac address
      emergencyVal = 'I'; // no request for emergency stop yet
      String package = String (startbit) + String(separator) + String(MacADDR) +
                       String(separator) + String(MacADDRCon) + String(separator) + String(emergencyVal) +
                       String(separator) + String(stopbit);
      package.toCharArray(messageOut, package.length() + 1);
      transmitmsg();
      firstMessage = 0;
    }





    if (MacADDRRec != " " && MacADDRConRec != " " && emergencyValRec != " " && stopbitRec != " " &&
        startbitRec != " " && separatorRec != " ")  {
      String package = String (startbit) + String(separator) + String(MacADDR) +
                       String(separator) + String(MacADDRCon) + String(separator) + String(emergencyVal) +
                       String(separator) + String(stopbit);
      package.toCharArray(messageOut, package.length() + 1);
      transmitmsg();

    }

=======
>>>>>>> parent of b25c5b7... lavet ting om
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

    MacADDRCon = 'C';
  }

  else {
    Serial.println("Mac-address not fetched or connection not available");
    Serial.println("Please restart");
    while (1)  {
      // do nothing
    }
  }
}
