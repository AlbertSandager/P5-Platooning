import RPi.GPIO as GPIO   # Import the GPIO library.
import time               # Import time library


GPIO.setmode(GPIO.BOARD)  # Set Pi to use pin number when referencing GPIO pins.
                          # Can use GPIO.setmode(GPIO.BCM) instead to use 
                          # Broadcom SOC channel names.


GPIO.setup(12, GPIO.OUT)  # Set GPIO pin 12 to output mode.
GPIO.setup(16, GPIO.OUT)  # Set GPIO pin 12 to output mode.
GPIO.setup(18, GPIO.OUT)  # Set GPIO pin 12 to output mode.
motorpwm = GPIO.PWM(12, 100)   # Initialize PWM on pwmPin 100Hz frequency


# main loop of program
dc=0                               # set dc variable to 0 for 0%
motorpwm.start(dc)                      # Start PWM with 0% duty cycle

GPIO.output(18, 1)
motorpwm.ChangeDutyCycle(8)
time.sleep(10)
GPIO.output(18, 0)


#GPIO.output(18, 1)
#pwm.ChangeDutyCycle(6)
#time.sleep(6)
#GPIO.output(18, 0)

motorpwm.stop()                         # stop PWM
GPIO.cleanup()                     # resets GPIO ports used back to input mode