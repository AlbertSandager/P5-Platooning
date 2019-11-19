void connectionControl()  {

  //Sending AT+RESET to make sure it connects to the other device (only done once)
  delay(700);
  if (ATcntrlVar == 0)  {
    for (int i = 0; i < sizeof(ATcommand); i++) {
      BTserial.write(ATcommand[i]); //send the command
      //Serial.println(ATcommand[i]);
    }
    ATcntrlVar = 1;
    //Serial.println("");
  }

  //Receiving the OK+CONN from the device if its connected
  delay(100);
  while (WHILEcntrl == 0) {
    for (int k = 0; k < sizeof(OKRESET) + 1; k++)  { // do it 50 times just to be sure
      if (BTserial.available()) {
        OKRESET[k] = BTserial.read(); //fill up the receiving array
        Serial.print(OKRESET[k]); //print the response from the HM-10
      }
    }

    //isolating the OK+RESET message
    Serial.println("");
    String connectionStatusStr1(OKRESET); //convert char array to string
    char CSseperator1 = connectionStatusStr1.indexOf('O');  //set up seperator
    char CSseperator12 = connectionStatusStr1.indexOf('T') + 1;  //set up seperator
    CSisolated = connectionStatusStr1.substring(CSseperator1, CSseperator12);
    delay(50);

    while (CSisolated == "OK+RESET") {
      //Serial.println("I have read OK+reset");
      if (BTserial.available()) {
        for (int k = 0; k < sizeof(OKLOST) + 1; k++)  { // do it 50 times just to be sure
          OKLOST[k] = BTserial.read(); //fill up the receiving array
          Serial.print(OKLOST[k]); //print the response from the HM-10
        }
        String connectionStatusStr2(OKLOST); //convert char array to string
        char CSseperator2 = connectionStatusStr2.indexOf('O');  //set up seperator
        char CSseperator22 = connectionStatusStr2.indexOf('T') + 1;  //set up seperator
        CSisolated = "";
        CSisolated = connectionStatusStr2.substring(CSseperator2, CSseperator22);
      }

      delay(100);
      while (CSisolated == "OK+LOST")  {
        delay(50);
        //Serial.println("I have read OK+LOST");
        if (BTserial.available()) {
          for (int k = 0; k < sizeof(OKCONN) + 1; k++)  { // do it 50 times just to be sure
            OKCONN[k] = BTserial.read(); //fill up the receiving array
            Serial.print(OKCONN[k]); //print the response from the HM-10
          }
          String connectionStatusStr3(OKCONN); //convert char array to string
          char CSseperator3 = connectionStatusStr3.indexOf('O');  //set up seperator
          char CSseperator33 = connectionStatusStr3.indexOf('N') + 2;  //set up seperator
          CSisolated = "";
          CSisolated = connectionStatusStr3.substring(CSseperator3, CSseperator33);
          //Serial.println(CSisolated);
        }
        Serial.println("");
        if (CSisolated == "OK+CONN")  {
          Serial.println("Connection established");
          connectionbool = true;
          caseChoice = 'M';
          WHILEcntrl = 1;
        }
      }
    }
  }
}



void MacADDRcontrol() {
  //sending command to get the mac address
  if (tempMacADDR[0] == NULL)  {  //only send the message if our Mac adress is non-existant
    for (int i = 0; i < 8; i++) {
      BTserial.write(ADDRcommand[i]); //send the command
      //Serial.print(ADDRcommand[i]);
    }
    Serial.println("");
  }

  //Serial.println("");
  //fill up array with the received mac address
  delay(100);

  for (int k = 0; k < sizeof(tempMacADDR) + 1; k++)  { // do it 50 times just to be sure
    if (BTserial.available()) {
      tempMacADDR[k] = BTserial.read(); //fill up the receiving array
      //Serial.print(tempMacADDR[k]);
    }
  }

  //isolate so the mac address looks as it should
  String MacADDRstr(tempMacADDR); //convert char array to string
  char MacSeperator = MacADDRstr.indexOf(':') + 1;  //set up seperator
  MacADDR = MacADDRstr.substring(MacSeperator, ' '); //make a string with only the mac adress.
  if (MacADDR.length() == 12 && MacADDRbool == false) {
    Serial.println("Mac-address is:");
    Serial.println(MacADDR);
    MacADDRbool = true;
  }

  //check if the lenght of the mac address is correct
  delay(50);
  MacADDRcontrolInt = MacADDRcontrolInt + 1;
  if (MacADDR.length() != 12 && MacADDRcontrolInt >= 20)  {
    Serial.println("Wrong Mac-adress length!");
    Serial.println("Returning to menu");
    for (int j = 0; j < 15; j++)  {
      platooningMode = NULL;
      tempMacADDR[j] = NULL;
      MacADDRcontrolInt = 0;
    }
    MacADDRbool = false;
    caseChoice = 'M';
  }
}
