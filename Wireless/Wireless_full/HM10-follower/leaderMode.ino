void leaderMode() {
  if (MacADDRbool == true && connectionbool == true) {
    wantedStatus = 'L';
    confirmation = 'W';
    STOPstatus = 'C';
    String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(platooningMode) + String(separator) + String(wantedStatus) + String(separator) + String(confirmation)
                     + String(separator) + String(STOPstatus) + String(separator) + String(stopbit);
    package.toCharArray(messageOut, package.length());
    packageLen = package.length();
    Serial.println("Package length: ");
    Serial.println(package.length());
    transmit();
    

    
    
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






/*
char separator = ':';
char startbit = 'P'; // P
String MacADDR;   // Mac adress of HM-10
char platooningMode = NULL;  // L = leader     F = follower
char wantedStatus = ' ';  // L = leader    // F = follower
char confirmation = ' '; // G = good to go = confirmed     // D = denied    // W = waiting for request
char STOPstatus = ' ';     // C = continue     S = STOP
char stopbit = 'Q';  // Q
 */
