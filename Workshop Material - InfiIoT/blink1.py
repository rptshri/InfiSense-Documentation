import RPi.GPIO as GPIO
import time

try:
	# Set up the GPIO channels 
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(14, GPIO.OUT)


	# Output to pin 12
	while True:
		GPIO.output(14, True)
		time.sleep(1)
		GPIO.output(14, False)
		time.sleep(1)

except KeyboardInterrupt:
	GPIO.cleanup()
