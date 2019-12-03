unsigned long starttime;
unsigned long endtime;
int wiredInput = 9;
int choker = 0;

void setup()
{
  pinMode(wiredInput, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.flush();
  // set the data rate for the SoftwareSerial port
  Serial3.begin(9600);
  Serial3.flush();
}

void loop()
{
  if (choker == 0)
  {
    String out = String('G');
    Serial3.print(out);    // sender det der blev skrevet i serial monitor over RF
    Serial3.flush();
    starttime = micros();      // take the starttime of the transmission
    choker = 1;
  }
  
  if (digitalRead(wiredInput) == HIGH)  {
    endtime = micros();                         // stop the timer
    unsigned long total = endtime - starttime;  //calculate total transmission time
    Serial.println(total);
    delay(1000);
    choker = 0;
  }
}
