void leaderMode() {
  //if mac address is received and the connection is ready. Send out the full message in followermode
  if (MacADDRbool == true && connectionbool == true) {
    wantedStatus = 'L';
    confirmation = 'W';
    STOPstatus = 'C';

    String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(platooningMode) + String(separator) + String(wantedStatus) + String(separator) + String(confirmation)
                     + String(separator) + String(STOPstatus) + String(separator) + String(stopbit);

    package.toCharArray(messageOut, package.length() + 1);


    //main thing runs HERE!!!
    while (statusChange == 0) {
      digitalWrite(13, HIGH);
      
      transmitmsg();
      
    }
  }

  else if (MacADDRbool == false || connectionbool == false) {
    Serial.print("Mac-address not fetched or connection not available");
  }
  delay(5000);
}
