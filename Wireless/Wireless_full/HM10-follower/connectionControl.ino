void connectionControl()  {
  delay(20);
  if (connectionStatus[0] == NULL)  {  //only send the message if our Mac adress is non-existant
    //Serial.print("ConnectionStatus = NULL");
    for (int k = 0; k < 100; k++)  { // do it 50 times just to be sure
      if (BTserial.available()) {
        connectionStatus[k] = BTserial.read(); //fill up the receiving array
        //Serial.print(connectionStatus[k]); //print the response from the HM-10
      }
    }
    String connectionStatusStr(connectionStatus); //convert char array to string
    //Serial.println(connectionStatusStr);
    char CSseperator = connectionStatusStr.indexOf('O');  //set up seperator
    String CSisolated = connectionStatusStr.substring(CSseperator, ' ');
    if (CSisolated == "OK+CONN")  {
      Serial.println("Connection established");
      caseChoice = 'M';
    }
  }
}

void MacADDRcontrol() {
  if (tempMacADDR[0] == NULL)  {  //only send the message if our Mac adress is non-existant
    for (int i = 0; i < 8; i++) {
      BTserial.write(ADDRcommand[i]); //send the command
      //Serial.println(ADDRcommand[i]);
    }
  }
  delay(50);
  for (int k = 0; k < 49; k++)  { // do it 50 times just to be sure
    if (BTserial.available()) {
      tempMacADDR[k] = BTserial.read(); //fill up the receiving array
      //Serial.println(tempMacADDR[k]);
    }
  }

  String MacADDRstr(tempMacADDR); //convert char array to string
  char MacSeperator = MacADDRstr.indexOf(':') + 1;  //set up seperator
  MacADDR = MacADDRstr.substring(MacSeperator, ' '); //make a string with only the mac adress.
  if (MacADDR.length() == 12) {
    Serial.println("Mac-address is:");
    Serial.println(MacADDR);
    caseChoice = '3';
  }

  delay(50);
  MacADDRcontrolInt = MacADDRcontrolInt + 1;
  if (MacADDR.length() != 12 && MacADDRcontrolInt >= 20)  {
    Serial.println("Wrong Mac-adress length!");
    Serial.println("Returning to menu");
    for (int j = 0; j < 15; j++)  {
      platooningMode[j] = NULL;
      tempMacADDR[j] = NULL;
      MacADDRcontrolInt = 0;
    }
    caseChoice = 'M';
  }
}
