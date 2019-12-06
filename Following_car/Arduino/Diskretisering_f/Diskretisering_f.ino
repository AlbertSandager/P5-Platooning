float K_p_distance = 17.39;
float K_i_distance = 1;
float K_v_distance = 1;

float PWM_DC = 0;
float PWM_last_DC = 0;
float PWM_real_DC = 0;
float Error_DC = 0;
float Error_last_DC = 0;
float D_ref = 0.324;
float D_measured = 0;
float V_measured = 0;

void setup() {

}

void loop() {

  //D_measured = output of distance meter.
  Error = D_measured - D_ref;
  PWM_DC = ((Error_DC - Error_last_DC)*K_p_distance) + (K_i_distance*Error_last_DC*T) + PWM_last_DC;
  PWM_real_DC = PWM_DC - (K_v_distance * V_measured);

  //Sæt motor ting til PWMa
  
  Error_last_DC = Error_DC;
  PWM_last_DC = PWM_DC;
}
