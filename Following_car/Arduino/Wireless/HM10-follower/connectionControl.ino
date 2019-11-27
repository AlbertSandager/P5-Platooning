void MacADDRcontrol() {
  //sending command to get the mac address
  if (tempMacADDR[0] == NULL)  {  //only send the message if our Mac adress is non-existant
    for (int i = 0; i < 8; i++) {
      BTserial.write(ADDRcommand[i]); //send the command
    }
    Serial.println("");
  }
  //fill up array with the received mac address
  delay(100);

  for (int k = 0; k < sizeof(tempMacADDR) + 1; k++)  { // do it 50 times just to be sure
    if (BTserial.available()) {
      tempMacADDR[k] = BTserial.read(); //fill up the receiving array
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
    for (int j = 0; j < 15; j++)  {
      tempMacADDR[j] = NULL;
      MacADDRcontrolInt = 0;
    }
    MacADDRbool = false;
    //    caseChoice = 'M';
  }
}
