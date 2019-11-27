void transmitmsg() {
  for (int i = 0; i < sizeof(messageOut) + 1; i++)  {
    if (messageOut[i] != 10 && messageOut[i] != 13)
    {
            digitalWrite(3, LOW);
      BTserial.write(messageOut[i]);  // transmit the predetermined character
           digitalWrite(3, HIGH);
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

  emergencyValRec = BTserial.readStringUntil(':');
  BTserial.read();

  confirmationRec = BTserial.readStringUntil(':');
  BTserial.read();

  stopbitRec = BTserial.readStringUntil(':');
  BTserial.read();
}
