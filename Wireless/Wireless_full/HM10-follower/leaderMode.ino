void leaderMode() {
  //Serial.println("You chose leader mode");
  carStatus[30] = "Leader#";

  if (MacADDR[0] == NULL)  {  //only send the message if our Mac adress is non-existant
    for (int i = 0; i < 8; i++) {
      BTserial.write(ADDRcommand[i]); //send the command
      Serial.print(ADDRcommand[i]);
    }
  }

  delay(200);
  Serial.println(""); //line new
  for (int k = 0; k < 49; k++)  { // do it 50 times just to be sure
    if (BTserial.available()) {
      MacADDR[k] = BTserial.read(); //fill up the receiving array
      Serial.print(MacADDR[k]); //print the response from the HM-10
    }
  }
  String MacADDRstr(MacADDR); //convert char array to string
  char MacSeperator = MacADDRstr.indexOf(':') + 1;  //set up seperator
  String MacADDRisolated = MacADDRstr.substring(MacSeperator, ' '); //make a string with only the mac adress. 
  // yeet the rest of the response away
  Serial.print(MacADDRisolated);//print it
  //caseChoice = 
}
