void followerMode() {
  //if mac address is received and the connection is ready. Send out the full message in followermode
  if (MacADDRbool == true) {
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

    //MacADDRCon = 'C';
    //confirmation = 'W';



    digitalWrite(13, HIGH);



    //Serial.println(MacADDRRec);
    //Serial.println(MacADDRConRec);
    //Serial.println(emergencyValRec);

    //MacADDRCon = 'C';
  }

  else {
    Serial.println("Mac-address not fetched or connection not available");
    Serial.println("Please restart");
    while (1)  {
      // do nothing
    }
  }
}
