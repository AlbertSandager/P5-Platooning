void followerMode() {
int tStart=0;
int tStop=0;

if(digitalRead(3)==LOW){ 
tStart=millis();
}  

  receivemsg();
tStop = millis();
Serial.println((tStop-tStart));


//  Serial.println(MacADDRRec);
//  Serial.println(platooningModeRec);
//  Serial.println(wantedStatusRec);
//  Serial.println(confirmationRec);
//  Serial.println(STOPstatusRec);
}
