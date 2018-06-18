import serial
from time import sleep
import sys
import pymysql.cursors
from sql import update

#database connection
COM = "COM4"
BAUD = 9600
Data = ['']
ser = serial.Serial(COM, BAUD, timeout = .1)

print("wait")
#sleep(5)
print(ser.name)

if("-m" in sys.argv or "--monitor" in sys.argv):
	monitor = True
else:
	monitor= False

while True:
	val = str(ser.readline().decode().strip('\r\n'))
	valA = val.split("/")
	#upd(valA)
	if(monitor == False):        
            #print(val, end="\r", flush=True)
            
            #data.append(print(val,end="\r",flush=True))
            for v in valA:
                sleep(3)
                if len(v) > 0:
                    x = update(v)
                    print(x)
                #print(v)
                #Data.append(v)
                #i+=1
                #print(i)
                #print(v)
                #print(i)
                #if(i == 2):
                    #s=""
                    #for i in range(Data):
                    #    s+=str(i)
                    #print(s)
                    #break
                    #break
            #print(Data)
            #data = []
            #update(val, end="\r", flush=True)
            #sleep(10)
            #upd(val)
            #a = str(tag.getArtist(val, end="\r", flush=True))
            #upd(print(val, end="\r", flush=True))
    
    
    
