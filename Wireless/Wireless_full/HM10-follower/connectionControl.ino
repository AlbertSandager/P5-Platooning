void connectionControl()  {
  delay(300);
  if (ATcntrlVar == 0)  {
    for (int i = 0; i < sizeof(ATcommand); i++) {
      BTserial.write(ATcommand[i]); //send the command
      Serial.println(ATcommand[i]);
    }
    ATcntrlVar = 1;
  }

  delay(100);
  while (WHILEcntrl == 0) {
    for (int k = 0; k < sizeof(connectionStatus) + 1; k++)  { // do it 50 times just to be sure
      if (BTserial.available()) {
        connectionStatus[k] = BTserial.read(); //fill up the receiving array
        Serial.print(connectionStatus[k]); //print the response from the HM-10
      }
    }
    Serial.println("");
    String connectionStatusStr1(connectionStatus); //convert char array to string
    char CSseperator1 = connectionStatusStr1.indexOf('O');  //set up seperator
    char CSseperator12 = connectionStatusStr1.indexOf('T') + 1;  //set up seperator
    CSisolated = connectionStatusStr1.substring(CSseperator1, CSseperator12);
    Serial.println("CS isolated is:");
    Serial.println(CSisolated);
    delay(50);
    for (int i = 0; i < sizeof(connectionStatus) + 1; i++) {
      connectionStatus[i] = ' ';
    }
    while (CSisolated == "OK+RESET") {
      Serial.println("I have read OK+reset");
      if (BTserial.available()) {
        for (int k = 0; k < sizeof(connectionStatus) + 1; k++)  { // do it 50 times just to be sure
          connectionStatus[k] = BTserial.read(); //fill up the receiving array
          Serial.print(connectionStatus[k]); //print the response from the HM-10
        }
        String connectionStatusStr2(connectionStatus); //convert char array to string
        char CSseperator2 = connectionStatusStr2.indexOf('O');  //set up seperator
        char CSseperator22 = connectionStatusStr2.indexOf('T') + 1;  //set up seperator
        CSisolated = "";
        CSisolated = connectionStatusStr2.substring(CSseperator2, CSseperator22);
      }

      delay(100);
      while (CSisolated == "OK+LOST")  {
        delay(50);
        Serial.println("I have read OK+LOST");
        if (BTserial.available()) {
          for (int k = 0; k < sizeof(connectionStatus) + 1; k++)  { // do it 50 times just to be sure
            connectionStatus[k] = BTserial.read(); //fill up the receiving array
            Serial.print(connectionStatus[k]); //print the response from the HM-10
          }
          String connectionStatusStr3(connectionStatus); //convert char array to string
          char CSseperator3 = connectionStatusStr3.indexOf('O');  //set up seperator
          char CSseperator33 = connectionStatusStr3.indexOf('T') + 1;  //set up seperator
          CSisolated = "";
          CSisolated = connectionStatusStr3.substring(CSseperator3, CSseperator33);
          Serial.println(CSisolated);
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














/*
  delay(100);
  if (connectionStatus[0] == NULL)  {  //only send the message if our Mac adress is non-existant
    //Serial.println("im in this bitch");
    //Serial.print("ConnectionStatus = NULL");

    for (int k = 0; k < sizeof(connectionStatus) + 1; k++)  { // do it 50 times just to be sure
      if (BTserial.available()) {
        connectionStatus[k] = BTserial.read(); //fill up the receiving array
        Serial.print(connectionStatus[k]); //print the response from the HM-10
      }
    }

    String connectionStatusStr1(connectionStatus); //convert char array to string
    //Serial.println(connectionStatusStr);
    char CSseperator1 = connectionStatusStr1.indexOf('O');  //set up seperator
    String CSisolated = connectionStatusStr1.substring(CSseperator1, ' ');

    for (int i = 0; i < sizeof(connectionStatus); i++)  {
      connectionStatus[i] = NULL;
    }

    while (CSisolated == "OK+RESET")  {
      for (int k = 0; k < sizeof(connectionStatus) + 1; k++)  { // do it 50 times just to be sure
        if (BTserial.available()) {
          connectionStatus[k] = BTserial.read(); //fill up the receiving array
          //Serial.print(connectionStatus[k]); //print the response from the HM-10
          //Serial.print("Jeg printer i OK+RESET");
        }
      }

      String connectionStatusStr2(connectionStatus); //convert char array to string
      //Serial.println(connectionStatusStr);
      char CSseperator2 = connectionStatusStr2.indexOf('O');  //set up seperator
      CSisolated = connectionStatusStr2.substring(CSseperator2, ' ');
    }

    for (int i = 0; i < sizeof(connectionStatus); i++)  {
      connectionStatus[i] = NULL;
    }

    while (CSisolated == "OK+LOST")  {
      for (int k = 0; k < sizeof(connectionStatus) + 1; k++)  { // do it 50 times just to be sure
        if (BTserial.available()) {
          connectionStatus[k] = BTserial.read(); //fill up the receiving array
          //Serial.print(connectionStatus[k]); //print the response from the HM-10
          //Serial.print("Jeg printer i OK+LOST");
        }
      }

      String connectionStatusStr3(connectionStatus); //convert char array to string
      //Serial.println(connectionStatusStr);
      char CSseperator3 = connectionStatusStr3.indexOf('O');  //set up seperator
      CSisolated = "";
      CSisolated = connectionStatusStr3.substring(CSseperator3, ' ');
      Serial.println(CSisolated);

      for (int i = 0; i < sizeof(connectionStatus); i++)  {
        connectionStatus[i] = NULL;
      }
    }


    //      while (CSisolated == "OK+LOST")  {
    //        for (int k = 0; k < sizeof(connectionStatus) + 1; k++)  { // do it 50 times just to be sure
    //          if (BTserial.available()) {
    //            connectionStatus[k] = BTserial.read(); //fill up the receiving array
    //            //Serial.print(connectionStatus[k]); //print the response from the HM-10
    //          }
    //        }
    //
    //        String connectionStatusStr(connectionStatus); //convert char array to string
    //        //Serial.println(connectionStatusStr);
    //        char CSseperator = connectionStatusStr.indexOf('O');  //set up seperator
    //        String CSisolated = connectionStatusStr.substring(CSseperator, ' ');
    //      }
    if (CSisolated == "OK+CONN")  {
      Serial.println("Connection established");
      connectionbool = true;
      caseChoice = 'M';
    }
  }
  }
*/


void MacADDRcontrol() {
  if (tempMacADDR[0] == NULL)  {  //only send the message if our Mac adress is non-existant
    for (int i = 0; i < 8; i++) {
      BTserial.write(ADDRcommand[i]); //send the command
      //Serial.println(ADDRcommand[i]);
    }
  }
  delay(50);
  for (int k = 0; k < sizeof(tempMacADDR) + 1; k++)  { // do it 50 times just to be sure
    if (BTserial.available()) {
      tempMacADDR[k] = BTserial.read(); //fill up the receiving array
      //Serial.println(tempMacADDR[k]);
    }
  }

  String MacADDRstr(tempMacADDR); //convert char array to string
  char MacSeperator = MacADDRstr.indexOf(':') + 1;  //set up seperator
  MacADDR = MacADDRstr.substring(MacSeperator, ' '); //make a string with only the mac adress.
  if (MacADDR.length() == 12 && MacADDRbool == false) {
    Serial.println("Mac-address is:");
    Serial.println(MacADDR);
    MacADDRbool = true;
  }

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
