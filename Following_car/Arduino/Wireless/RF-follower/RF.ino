void sendmsg(int x){
    String msg = '#' + String(x) + '!' + String(x) + '!' + String(x) + '/';
  mySerial.print(msg);                              //Send "tal" with the RF-module. 
  Serial.println(""); Serial.print("String sent to next car: "); Serial.print(msg); Serial.println(""); //Serial print for debugging
  mySerial.flush();
  delay(10);
}


void receivemsg() {
  if (mySerial.available() > 0 )
  {
    mySerial.readBytesUntil('/', instring, NRCHAR); //break character = /
    mySerial.flush();
    String str = String(instring);
    char startChar = str.charAt(0);                //Check the first character in the array
    if (startChar == '#') {                        //If the start-character is correct, proceed to analyze the data.
      splitUp(str);                                //split up the received string
    }
  }
}



void splitUp(String A ) //Function for splitting up the received string. Using seperators, it makes 3 substrings and converts them to ints. 
{
  int startSeperator = A.indexOf('#') + 1; 
  int seperatorEt = A.indexOf('!');
  int seperatorTo = A.indexOf('!', seperatorEt + 1);
  int seperatorTre = A.indexOf('/');
  String sub1 = A.substring(startSeperator, seperatorEt);
  String sub2 = A.substring(seperatorEt + 1, seperatorTo);
  String sub3 = A.substring(seperatorTo + 1, seperatorTre);

  val1 = sub1.toInt(); //value for motorspeed
  val2 = sub2.toInt(); //value for servo
  val3 = sub3.toInt(); //carStop
  }
