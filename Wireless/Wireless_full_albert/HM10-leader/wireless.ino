void transmitmsg() {
  for (int i = 0; i < sizeof(messageOut) + 1; i++)  {
    if (messageOut[i] != 10 && messageOut[i] != 13)
    {
      BTserial.write(messageOut[i]);  // transmit the predetermined character
      delay(5);
      Serial.print(messageOut[i]);
      //Serial.println("Im sending shit");
    }
  }
  //Serial.println("");
}

void receivemsg() {
  for (int k = 0; k < sizeof(messageIn) + 1; k++)  { // do it 50 times just to be sure
    if (BTserial.available()) {
      messageIn[k] = BTserial.read(); //fill up the receiving array

    }
  }
}
 
