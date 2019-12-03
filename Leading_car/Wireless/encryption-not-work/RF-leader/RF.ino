//sending message
void sendmsg() {
  String msg = String(startbyte) + String(address) + String(seperator) + String(addressCon) + String(seperator) + String(emergencyVal) + String(stopbyte);

  for (int i = 0; i < 3; i++)
  {
    aesDecrypt (keyLength[i]);
    //delay(2000);
  }

  mySerial.print(encryptMsgout);                              //Send "tal" with the RF-module.
    Serial.println("Following information sent:");
    Serial.println(encryptMsgout);
  //  Serial.println(""); Serial.print("String sent to next car: "); Serial.print(msg); Serial.println(""); //Serial print for debugging
  mySerial.flush();
}

//receiveing message
void receivemsg() {
  listening = true;
  if (mySerial.available() > 0 )
  {
    mySerial.readBytesUntil(stopbyte, instring, NRCHAR); //break character = /
    mySerial.flush();

    String str = String(instring);
    str.getBytes(encryptMsgin, 12);

    for (int i = 0; i < 3; i++)
    {
      aesDecrypt (keyLength[i]);
      delay(2000);
    }

    String string = decryptMsgin;

    Serial.println("Following information received:");
    Serial.println(string);
    Serial.println();

    char startChar = string.charAt(0);                //Check the first character in the array
    if (startChar == startbyte) {                        //If the start-character is correct, proceed to analyze the data.
      splitUp(string);                                //split up the received string
    }
  }
}


//splitting message up
void splitUp(String A ) //Function for splitting up the received string. Using seperators, it makes 3 substrings and converts them to ints.
{

  char startSeperator = A.indexOf(startbyte) + 1;
  char seperatorEt = A.indexOf(seperator);
  char seperatorTo = A.indexOf(seperator, seperatorEt + 1);
  char seperatorTre = A.indexOf(stopbyte);
  addressRec = A.substring(startSeperator, seperatorEt);
  addressConRec = A.substring(seperatorEt + 1, seperatorTo);
  emergencyValRec = A.substring(seperatorTo + 1, seperatorTre);

  if (addressRecOld != " ") {
    addressCon = 'M';
  }
  if (addressRecOld == addressRec) {
    addressCon = 'R';
  }
  else if (addressRecOld != addressRec && addressRecOld != " ") {
    addressCon = 'W';
  }
  if (digitalRead(4) == LOW)  {
    emergencyVal = 'Y';
  }
  else {
    emergencyVal = 'N';
  }
  if (digitalRead(8) == LOW) {
    address = "HCY5RR4N68KT"; // 1 character changed
  }
  else {
    address = "HCY5RR4N68KW";
  }


  listening = false;

}


void aesEncrypt(int bits) {
  aes.iv_inc();

  byte iv [N_BLOCK] ;
  int plainPaddedLength = sizeof(plain) + (N_BLOCK - ((sizeof(plain) - 1) % 16)); // length of padded plaintext [B]
  byte cipher [plainPaddedLength]; // ciphertext (encrypted plaintext)
  byte check [plainPaddedLength]; // decrypted plaintext

  aes.set_IV(myIv);
  aes.get_IV(iv);

  aes.do_aes_encrypt(plain, sizeof(plain), cipher, key, bits, iv);
  encryptMsgout = cipher;
}


void aesDecrypt (int bits) {
  aes.iv_inc();

  byte iv [N_BLOCK] ;
  int plainPaddedLength = sizeof(plain) + (N_BLOCK - ((sizeof(plain) - 1) % 16)); // length of padded plaintext [B]
  byte check [plainPaddedLength]; // decrypted plaintext

  aes.set_IV(myIv);
  aes.get_IV(iv);

  aes.do_aes_decrypt(encryptMsgin, aes.get_size(), check, key, bits, iv);
  decryptMsgin = check;

}
