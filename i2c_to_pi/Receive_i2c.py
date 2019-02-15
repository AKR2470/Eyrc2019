import smbus
import aruco_detect2
import time
from hlsas import color_detect

bus = smbus.SMBus(1)
address1 = 0x08
address2 = 0x04
g = 0
g_previous = -1

c = 0


def access1():
    return  bus.read_byte(address1)

def access2():
    return bus.read_byte(address2)

    
def send_data1(data):
    bus.write_byte(address1, data)
    
def send_data2(data):
    bus.write_byte(address2, data)
    
def aruco_detect(g):
	
	
	    returned = aruco_detect2.cap_aruco_detect(g)
	    return returned  #send_data(returned) #send 2 to i2c for aruco detected
			
        
            
if __name__ == "__main__":
                
                
                while(1):
                    g = access1()    # receive 0,1,2,3 for arudo detect call
                    """c = access2()"""
                    if ((g != g_previous) and (g >= 1 and g <= 4)):
                        ID = aruco_detect(g)
                        print("#####################ID#########")
                        print("ID detected is ", ID)
		
                        if ID is not -1:
                            send_data1(ID)
                            g_previous = g
                            print("#############Data Sent###########")
                    """if ( c == 5 ):
                        color = color_detect()
                        send_data2(color)"""

		

	
