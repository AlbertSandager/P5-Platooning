float K_p = 17.39;
float K_i = 1;
float K_v = 1;

float PWM = 0;
float PWM_last = 0;
float PWM_real = 0;
float Error = 0;
float Error_last = 0;
float D_ref = 0.324;
float D_measured = 0;
float V_measured = 0;

void setup() {

}

void loop() {

  //D_measured = output of distance meter.
  Error = D_measured - D_ref;
  PWM = ((Error - Error_last)*K_p) + (K_i*Error_last*T) + PWM_last;
  PWM_real = PWM - (K_v * V_measured);

  //Sæt motor ting til PWMa
  
  Error_last = Error;
  PWM_last = PWM;
}
