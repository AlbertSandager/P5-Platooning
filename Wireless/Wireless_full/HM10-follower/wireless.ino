void transmit() {
  for (int i = 0; i == packageLen; i++)  {
    if (messageOut[i] != 10 && messageOut[i] != 13)
  {
    BTserial.write(messageOut[i]);  // transmit the predetermined character
    Serial.println("Im sending shit");
  }
  }
 
//  if (transmit != 10 & transmit != 13 & choker == 0)
//  {
//    BTserial.write(transmit);  // transmit the predetermined character
//  }
//  if (BTserial.available())
//  {
//    char receive = ' ';             // make an empty char to receive char
//    receive = BTserial.read();      // place the received char in the variable
//    if (receive == 'J') {           // if the received char is J
//      endtime = micros();          // stop the timer
//      unsigned long total = endtime - starttime; //calculate total transmission time
//      Serial.println("Total time is: ");
//      Serial.println(total);
//      receive = ' ';               // empty the char
//      delay(1000);
//      choker = 0;
//    }
//  }
}
