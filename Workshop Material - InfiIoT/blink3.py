import RPi.GPIO as GPIO
import time


print "Hit Ctrl+C to stop...";
try:
	# Set up the GPIO channels - 3 outputs, one input
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(14, GPIO.OUT)
	GPIO.setup(15, GPIO.OUT)
	GPIO.setup(18, GPIO.OUT)
	GPIO.setup(23, GPIO.IN, pull_up_down = GPIO.PUD_UP)

	t = 0.1
	while True:
		#do nothing while the button is not pushed.
		#ie, this will loop forever until GPIO.input(23) becomes 0
		while (GPIO.input(23) == 1):
			pass
		print "Ding!";
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
		GPIO.output(14,False)
		GPIO.output(15,True)
		GPIO.output(18,False)
		time.sleep(t)
		GPIO.output(14,True)
		GPIO.output(15,False)
		GPIO.output(18,False)
		time.sleep(t)
		GPIO.output(14,False)
		GPIO.output(15,False)
		GPIO.output(18,False)
		time.sleep(t)

except KeyboardInterrupt:
	GPIO.cleanup()
