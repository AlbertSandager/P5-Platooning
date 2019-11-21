void leaderMode() {
  //if mac address is received and the connection is ready. Send out the full message in leadermode
  if (MacADDRbool == true && connectionbool == true) {
    wantedStatus = 'L';
    confirmation = 'W';
    STOPstatus = 'C';
    
    String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(platooningMode) + String(separator) + String(wantedStatus) + String(separator) + String(confirmation)
                     + String(separator) + String(STOPstatus) + String(separator) + String(stopbit);
    
    package.toCharArray(messageOut, package.length() + 1);
    //Serial.println("im in here, fucker");

    while (statusChange == 0) {
      //Serial.println("im also in here, fucker");
      transmitmsg();
      receivemsg();
    }


    //    for (int i = 0; i < package.length() + 1; i++)  {
    //    Serial.println(messageOut[i]);
    //    delay(100);
    //    }
  }
  else if (MacADDRbool == false || connectionbool == false) {
    Serial.print("Mac-address not fetched or connection not available");
  }
  delay(5000);
}
