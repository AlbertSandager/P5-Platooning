void transmitmsg() {
  for (int i = 0; i < sizeof(messageOut) + 1; i++)  {
    if (messageOut[i] != 10 && messageOut[i] != 13)
    {
      BTserial.write(messageOut[i]);  // transmit the predetermined character
      //Serial.print(messageOut[i]);
      //delayMicroseconds(1200); //so it doesn't go too fast for the receiver
    }
  }
}


void receivemsg() {

  //Here the message is split up into the different values
  startbitRec = BTserial.readStringUntil('/');
  BTserial.read();

  separatorRec = BTserial.readStringUntil(':');
  BTserial.read();

  MacADDRRec = BTserial.readStringUntil(':');
  BTserial.read();

  MacADDRConRec = BTserial.readStringUntil(':');
  BTserial.read();

  emergencyValRec = BTserial.readStringUntil(':');
  BTserial.read();

  stopbitRec = BTserial.readStringUntil(':');
  BTserial.read();
}
