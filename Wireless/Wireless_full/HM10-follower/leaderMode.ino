void leaderMode() {
  //Serial.println("You chose leader mode");
  carStatus[30] = "Leader#";

  if (MacADDR[0] == NULL)  {
    char ADDRcommand[8] = "AT+ADDR?";
    for (int i = 0; i < 8; i++) {
      BTserial.write(ADDRcommand[i]);
      Serial.print(ADDRcommand[i]);
    }
  }

  delay(200);
  Serial.println("");
  for (int k = 0; k < 49; k++)  {
    if (BTserial.available()) {
      MacADDR[k] = BTserial.read();
      Serial.print(MacADDR[k]);
    }
  }
  String MacADDRstr(MacADDR);
  char MacSeperator = MacADDRstr.indexOf(':') + 1;
  String MacADDRisolated = MacADDRstr.substring(MacSeperator, ' ');
  Serial.print(MacADDRisolated);
  // if (digitalRead(button1) == HIGH) {  //choose leader mode
  // tempStatus = "leader#";
  // fetchID = Serial.Write(AT+getMacAddr);
  // combinedBluetoothName= strcat(tempStatus,fetchID);

  // if (digitalRead(button2) == HIGH)
  // tempStatus = "follower#";
  // fetchID = Serial.Write(AT+getMacAddr);
  // combinedBluetoothName= strcat(tempStatus,fetchID);
  //}
}
