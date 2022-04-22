import ipaddress
import sys

def inputInt(range1, range2):
	while 1:
		try:
			x = int(input())
		except ValueError:
			print("it must be a integer, try again")
		if(x <= range1 and x >= range2):
			return x
		print("value out of range, try again")

def inputInt():
	while 1:
		try:
			return = int(input())
		except ValueError:
			print("it must be a integer, try again")
		print("value out of range, try again")

def userFileFinder():

def nfcAESinput():

def userAESinput():

def AESvalidation():

def firstTimeSetup():
	print("We couldn't find any info file, plz, do you want to:")
	print("1) open a setup file")
	print("2) creat a new one?")
	inputIntRandVar = inputInt(1,2)
	if(inputIntRandVar == 1):
		userFileFinder()
	
	else if(inputIntRandVar == 2):
		print("What is the ip of your watch?")
		WatchIp = input()
		while 1:
			print("Plz repeat your answer")
			WatchIp2 = input()
			if(WatchIp2 == WatchIp):
				break
			print("not the same, plz repeat")
			WatchIp = input()

		print("What port is the password communication on your watch (standard is 25565)")
		port = inputInt()
		while 1:
			print("Plz repeat your answer")
			port2 = inputInt()
			if(port == port2):
				break
			print("not the same, plz repeat")
			port = inputInt()

		