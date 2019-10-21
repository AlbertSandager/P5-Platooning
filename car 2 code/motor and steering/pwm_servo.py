import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setup(3, GPIO.OUT)

servopwm=GPIO.PWM(3, 50)
servopwm.start(0)


def SetAngle(angle):
    duty = angle / 18 + 2
    GPIO.output(3, True)
    servopwm.ChangeDutyCycle(duty)
    time.sleep(1)
    GPIO.output(3, False)
    servopwm.ChangeDutyCycle(0)
    

#Med den math der eksistere i linje 12 er det kun intervallet mellem 0-40 der må bruges!
#0=helt til højre
#40=helt til venstre
SetAngle(20)    

SetAngle(0)
time.sleep(1)
SetAngle(40)
time.sleep(1)
SetAngle(0)
time.sleep(1)
SetAngle(40)
time.sleep(1)

servopwm.stop()
GPIO.cleanup()