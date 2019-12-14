
# coding: utf-8

# In[1]:


import numpy as np
import matplotlib.pyplot as plt
import time
import serial
import datetime


# In[2]:


# 1 rev = dist traveled is pitch of threaded rod

pitch = .8 # distance between threads in metric units (cm)
step_ang = 1.8 # degrees
steps_per_rev_x = 400 # number of steps to travel the distance equivalent to pitch
steps_per_rev_y = 400 # number of steps to travel the distance equivalent to pitch


# In[3]:


# Establish a serial connection with Arduino

ser = serial.Serial('/dev/cu.usbmodem14201', 9600)


# In[4]:


# Calibration: returns number of steps it takes to go from one side to the other in x and y

stepsx_tot = 0
stepsy_tot = 0

count = 0
while count < 1: 
    stepsx_tot = (str(ser.readline()))
    stepsy_tot = (str(ser.readline()))
    count +=1


# In[5]:


# prints number of steps it takes to go from one side to the other in x and y

'''
print(stepsx_tot)
print(stepsy_tot)
'''


# In[24]:


# User decides where they want the defined zero position to be from the home position using keyboard inputs to \
# move the collimator. The location from the home position is recorded and stored as variables ZeroX and ZeroY. 

ZeroX = 0
ZeroY = 0

while True:
    move = input("Input direction you wish to move to move collimator to zero position: 'u' for up, 'd' for down, 'l' for left and 'r' for right. When you are done, type 'done'")
    if move == 'u':
        ZeroY += pitch
        inputy=('y,' + str(steps_per_rev_y) + ',1')
        ser.write(str.encode(inputy))
    elif move == 'd':
        ZeroY -= pitch
        inputy=('y,' + str(steps_per_rev_y) + ',0')
        ser.write(str.encode(inputy))
    elif move == 'r':
        ZeroX += pitch
        inputx=('x,' + str(steps_per_rev_x) + ',0')
        ser.write(str.encode(inputx))
    elif move == 'l':
        ZeroX -= pitch
        inputx=('x,' + str(steps_per_rev_x) + ',1')
        ser.write(str.encode(inputx))
    elif move == 'done':
        break


# In[7]:


#Prints location of new zero position from home position

''''
print(ZeroX)
print(ZeroY)
'''


# In[8]:


# Determining region to scan from zero position


# In[7]:


Length_L = float(input("Input horizontal distance from center of detector to left end of region you want to scan (in cm) less than 20 cm"))


# In[8]:


Length_R = float(input("Input horizontal distance from center of detector to right end of region you want to scan (in cm) less than 20 cm"))


# In[9]:


# Checks to make sure inputs are valid

if (Length_L + Length_R) > 20:
    sys.exit("ERROR: Horizontal distance cannot be greater than 20 cm")


# In[10]:


Height_B = float(input("Input vertical distance from center of detector to bottom end of region you want to scan (in cm) less than 40 cm"))


# In[11]:


Height_T = float(input("Input vertical distance from center of detector to top end of region you want to scan (in cm) less than 40 cm"))


# In[12]:


# Checks to make sure inputs are valid

if (Height_B + Height_T) > 40:
    sys.exit("ERROR: Vertical distance cannot be greater than 40 cm")


# In[13]:


# position collimator to starting position in top left corner

start_x = Length_L
start_y = Height_T


# In[14]:


# steps to take to travel dist to starting position

start_stepsx = (start_x/pitch) * steps_per_rev_x
start_stepsy = (start_y/pitch) * steps_per_rev_y


# In[15]:


# Create a string to send to Arduino telling it which motor to move, how many steps, and in which direction

inputx=('x,' + str(start_stepsx) + ',1')
inputy=('y,' + str(start_stepsy) + ',1')


# In[16]:


# Sends the string to the Arduino and motors move

ser.write(str.encode(inputx))
time.sleep(2)
ser.write(str.encode(inputy))


# In[17]:


# granularity - distance between center of scanned spots (in cm)

gran = float(input("Input the granularity (distance between the center of scanned spots in cm)"))


# In[18]:


# Check to make sure that input is valid

if gran > (Length_L + Length_R) or gran > (Height_B + Height_T):
    sys.exit("ERROR: Incompatible input. Granularity cannot be larger than scanning region")


# In[19]:


# time for source to be at each position over detector

wait = float(input("Input time for source to be at each collection spot (in seconds)"))


# In[26]:


# Open a text file to store positions and corresponding time during the scan

Time_and_Positions = open(r'/Users/Elizabeth/Desktop/sourcepositions.txt', 'w+')


# In[27]:


# Positioning algorithm

# Determine total x and y distance traveled. This is used to know whether the collimator has reached the end of \
# the scanning region in x and y directions
x_travel_dist = Length_L + Length_R
y_travel_dist = Height_B + Height_T

#Set starting coordinates of collimator, which will be changed as the collimator moves
x_dist = 0
y_dist = y_travel_dist

#Record initial starting place position and time and collect data
t=0
while t <= wait: #wait over area for specified amount of time so data can be collected
    date = datetime.datetime.now().timestamp() #current unix timestamp
    Time_and_Positions.write("%5.2f %5.2f %5.2f\n" % (date, x_dist , y_dist)) #write timestamp and x and y position to text file
    time.sleep(1)
    t += 1


while y_dist >= 0:
    if x_dist <= (x_travel_dist + gran):
        #move over right to next region to be scanned
        move_x = (gran/pitch) * steps_per_rev_x #num of steps to take to move to next scanned region
        x_dist += gran #determining x position 
        inputmovex = 'x,' + str(move_x) + ',0' #string formation to send to Arduino to move x motor right to next region
        print('x =', end =" ") #print progress update
        print(x_dist)
        ser.write(str.encode(inputmovex)) #send string to Arduino to move x motor
        t=0
        while t <= wait: #wait over area for specified amount of time so data can be collected
            date = datetime.datetime.now().timestamp() #current unix timestamp
            Time_and_Positions.write("%5.2f %5.2f %5.2f\n" % (date, x_dist , y_dist)) #write timestamp and x and y position to text file
            time.sleep(1)
            t += 1
        
    else:
        if y_dist > 0:
            #move motor to end right
            inputmovex_toendR = 'xEND,' + '0' #string formation to send to Arduino to move x motor right to switch
            print('xend') #print progress update
            ser.write(str.encode(inputmovex_toendR)) #send string to Arduino
            time.sleep(5)
            #move motor to end left
            inputmovex_toendL = 'xEND,' + '1' #string formation to send to Arduino to move x motor left to switch and count steps
            print('xcount')
            ser.write(str.encode(inputmovex_toendL)) #send string to Arduino
            count=0 #wait for response from Arduino to get number of steps it took to get to the end 
            while count < 1: 
                stepsx_toend = (str(ser.readline()))
                count +=1
                
            #if stepsx_toend != stepsx_tot:
               # sys.exit("ERROR: System not calibrated. Total horizontal distnace different than calibration")
            
            time.sleep(3)
            
            #move down a row
            move_y = (gran/pitch) * steps_per_rev_y #num of steps to take to move down to next row of scanned region
            y_dist -= gran #determining y position
            x_dist = 0 #resetting x position back to 0
            inputmovey = 'y,' + str(move_y) + ',0' #string formation to send to Arduino to move y motor down
            print('y =', end =" ") #print progress update
            print(y_dist)
            ser.write(str.encode(inputmovey)) #send string to Arduino
            time.sleep(3)

            #move back to starting x position on left side
            reset = ZeroX - Length_L #distance needed to travel in x to start at beginning of scanning region from left side
            move_x = (reset/pitch) * steps_per_rev_x #num of steps to take to move right to start of scanning region in x
            inputmovex = 'x,' + str(move_x) + ',1' #string formation to send to Arduino to move x motor right
            print('xreset') #print progress update
            ser.write(str.encode(inputmovex)) #send string to Arduino
            t=0
            while t <= wait: #wait over area for specified amount of time so data can be collected
                date = datetime.datetime.now().timestamp()
                Time_and_Positions.write("%5.2f %5.2f %5.2f\n" % (date, x_dist , y_dist))
                time.sleep(1)
                t += 1
        else:
            inputmovey_toend = 'yEND,' + '0' #string formation to send to Arduino to move y motor down to switch and count steps
            print('yend') #print progress update
            ser.write(str.encode(inputmovey_toend)) #send string to Arduino
            count=0
            while count < 1: #wait for response from Arduino to get number of steps it took to get to the end
                stepsy_toend = (str(ser.readline()))
                count +=1
                
            #if stepsx_toend != stepsx_tot:
               # sys.exit("ERROR: System not calibrated. Total horizontal distnace different than calibration")  
                
            print("scan complete")
            Time_and_Positions.close() #close text file
            break 
    


# In[49]:


'''
print(stepsx_toend)
print(stepsy_toend)
'''


# In[43]:


'''
# reset to specified zero position

reset_x = Length_R
reset_y = Height_B

reset_stepsx = (reset_x/pitch) * steps_per_rev_x
reset_stepsy = (reset_y/pitch) * steps_per_rev_y


inputx=('x,' + str(reset_stepsx) + ',1')
inputy=('y,' + str(reset_stepsy) + ',1')

ser.write(str.encode(inputx))
time.sleep(5)
ser.write(str.encode(inputy))
'''

