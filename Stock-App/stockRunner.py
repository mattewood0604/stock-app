import subprocess
import time

timeStruct = time.localtime(time.time())
hour = timeStruct.tm_hour
minute = timeStruct.tm_min

dayStarted = 0

while 1:
	timeStruct = time.localtime(time.time())
	day = timeStruct.tm_wday
	hour = timeStruct.tm_hour
	minute = timeStruct.tm_min
	second = timeStruct.tm_sec
	if hour == 9 and minute == 20 and day < 5:
		print("----- DAY STARTED -----")
		print(hour, ":", minute, ":", second)
		subprocess.call(["./stockRunner.sh"]);
		dayStarted = 1
	elif dayStarted == 1:
		print("----- DAY OVER -----")
		print(hour, ":", minute, ":", second)
		dayStarted = 0

		if day == 4:
			print("----- WEEKEND -----")
			time.sleep(234000)
		else: 
			print("----- WEEKDAY -----")
			time.sleep(61200)
	else:
		print("---- SHORT SLEEP ----")
		print(hour, ":", minute, ":", second)
		time.sleep(30)
