void leaderMode() {
  //if mac address is received and the connection is ready. Send out the full message in followermode
<<<<<<< HEAD
  if (MacADDRbool == true && connectionbool == true) {
    emergencyVal = 'N';
    confirmation = 'W';

<<<<<<< HEAD
<<<<<<< HEAD
      package.toCharArray(messageOut, package.length() + 1);
      transmitmsg();
      firstMessage = 0;
      Serial.println("First message sent");
    }

    digitalWrite(13, HIGH);
=======
    String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(MacADDRCon) + String(separator) + String(emergencyVal) + String(separator) + String(stopbit);
=======
    String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(emergencyVal) + String(separator) + String(confirmation) + String(separator) + String(stopbit);
>>>>>>> parent of 11724f1... trying to fix :((((

    package.toCharArray(messageOut, package.length() + 1);
=======
  if (MacADDRbool == true) {
    //MacADDRCon = 'C';
    //confirmation = 'W';

    String package = String (startbit) + String(separator) + String(MacADDR) + String(separator) + String(MacADDRCon) + String(separator) + String(emergencyVal) + String(separator) + String(stopbit);

    package.toCharArray(messageOut, package.length() + 1);

>>>>>>> parent of b25c5b7... lavet ting om

    //main thing runs HERE!!!
    digitalWrite(13, HIGH);

<<<<<<< HEAD
    //main thing runs HERE!!!
<<<<<<< HEAD
    digitalWrite(13, HIGH);

    transmitmsg();
>>>>>>> parent of b25c5b7... lavet ting om
=======
    transmitmsg();
>>>>>>> parent of b25c5b7... lavet ting om
    receivemsg();

    //Serial.println(MacADDRRec);
    //Serial.println(MacADDRConRec);
    //Serial.println(emergencyValRec);

    //MacADDRCon = 'C';


=======
    while (statusChange == 0) {
      digitalWrite(13, HIGH);
      
      transmitmsg();
      
    }
>>>>>>> parent of 11724f1... trying to fix :((((
  }

  else if (MacADDRbool == false || connectionbool == false) {
    Serial.print("Mac-address not fetched or connection not available");
<<<<<<< HEAD
    //caseChoice = 'M';
=======
>>>>>>> parent of 11724f1... trying to fix :((((
  }
  delay(5000);
}

void analyze()  {
  
}
