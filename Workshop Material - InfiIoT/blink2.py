import RPi.GPIO as GPIO
import time

try:
	# Set up the GPIO channels 
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(14, GPIO.OUT)
	GPIO.setup(15, GPIO.OUT)
	GPIO.setup(18, GPIO.OUT)

	t = 0.1
	# Output to pin 12
	while True:
		GPIO.output(14,True)
		GPIO.output(15,False)
		GPIO.output(18,False)
		time.sleep(t)
		GPIO.output(14,False)
		GPIO.output(15,True)
		GPIO.output(18,False)
		time.sleep(t)
		GPIO.output(14,False)
		GPIO.output(15,False)
		GPIO.output(18,True)
		time.sleep(t)

except KeyboardInterrupt:
	GPIO.cleanup()
