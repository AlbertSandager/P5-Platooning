void transmitmsg() {
  for (int i = 0; i < sizeof(messageOut) + 1; i++)  {
    if (messageOut[i] != 10 && messageOut[i] != 13)
    {
      BTserial.write(messageOut[i]);  // transmit the predetermined character
      Serial.print(messageOut[i]);
      //Serial.println("Im sending shit");
    }
  }
  Serial.println("");
}

void receivemsg() {
  for (int k = 0; k < sizeof(messageIn) + 1; k++)  { // do it 50 times just to be sure
    if (BTserial.available()) {
      messageIn[k] = BTserial.read(); //fill up the receiving array

    }
  }
  char inString[4];

  while (Serial.available() > 0) {
    Serial.readBytesUntil('P', inString, 4);   // Read until break character
    
    MacADDRRec = Serial.readStringUntil(':'); // writes in the string all the inputs till a comma
    Serial.read();
    platooningModeRec = Serial.readStringUntil(':');
    Serial.read();
    wantedStatusRec = Serial.readStringUntil(':'); // writes in the string all the inputs till the end of line character
    Serial.read();
    confirmationRec = Serial.readStringUntil(':');
    Serial.read();
    STOPstatusRec = Serial.readStringUntil(':'); // writes in the string all the inputs till the end of line character

  }
      Serial.println(MacADDRRec);
}
