import RPi.GPIO as GPIO   # Import the GPIO library.
import time               # Import time library


GPIO.setmode(GPIO.BOARD)  # Set Pi to use pin number when referencing GPIO pins.
                          # Can use GPIO.setmode(GPIO.BCM) instead to use 
                          # Broadcom SOC channel names.


#setting pins to output or input
GPIO.setup(3, GPIO.OUT)
GPIO.setup(12, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)
GPIO.setup(18, GPIO.OUT)


# Initialize PWM on pwmPin 100Hz frequency
servopwm=GPIO.PWM(3, 50)
motorpwm = GPIO.PWM(12, 100)


# main loop of program starts here

# Start PWM with 0% duty cycle
servopwm.start(0)
motorpwm.start(0)                      


#function for setting the servo angle
def SetAngle(angle):
    duty = angle / 18 + 2
    GPIO.output(3, True)
    servopwm.ChangeDutyCycle(duty)
    time.sleep(1)
    GPIO.output(3, False)
    servopwm.ChangeDutyCycle(0)


#Med den math der eksistere i linje 31 er det kun intervallet mellem 0-40 der må bruges!
#0=helt til højre
#40=helt til venstre

#we are steering here    
SetAngle(22.5)
time.sleep(1)
SetAngle(0)
time.sleep(1)
SetAngle(22.5)
time.sleep(1)
SetAngle(45)
time.sleep(1)
SetAngle(22.5)
time.sleep(1)

#we are speedy here
GPIO.output(16, 1)
motorpwm.ChangeDutyCycle(6)
time.sleep(2)
GPIO.output(16, 0)

#we go backwards here
#GPIO.output(18, 1)
#pwm.ChangeDutyCycle(6)
#time.sleep(6)
#GPIO.output(18, 0)

#we stop here
servopwm.stop()
motorpwm.stop()                    # stop PWM
GPIO.cleanup()                     # resets GPIO ports used back to input mode
