void transmitmsg() {
  for (int i = 0; i < sizeof(messageOut) + 1; i++)  {
    if (messageOut[i] != 10 && messageOut[i] != 13)
    {
      BTserial.write(messageOut[i]);  // transmit the predetermined character
      delayMicroseconds(1200); //so it doesn't go too fast for the receiver
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

  platooningModeRec = BTserial.readStringUntil(':');
  BTserial.read();

  wantedStatusRec = BTserial.readStringUntil(':');
  BTserial.read();

  confirmationRec = BTserial.readStringUntil(':');
  BTserial.read();

  STOPstatusRec = BTserial.readStringUntil(':');
  BTserial.read();

  stopbitRec = BTserial.readStringUntil(':');
  BTserial.read();
}
