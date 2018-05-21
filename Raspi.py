import serial
import numpy as np
import pygame
#import time
#import string

# Laster lyder:
keys = ['a2', 'a4', 'a8', 'b2', 'b4', 'b8', 'c2', 'c4', 'c8', 'd2', 'd4', 'd8', 'e2', 'e4', 'e8', 'f2', 'f4', 'f8', 'g2', 'g4', 'g8']
files = ['/media/pi/U2_HVIT/A-2 (copy 2).wav',
'/media/pi/U2_HVIT/A-4 (copy 2).wav',
'/media/pi/U2_HVIT/A-8 (copy 2).wav',
'/media/pi/U2_HVIT/B-2 (copy 2).wav',
'/media/pi/U2_HVIT/B-4 (copy 2).wav',
'/media/pi/U2_HVIT/B-8 (copy 2).wav',
'/media/pi/U2_HVIT/C-2 (copy 2).wav',
'/media/pi/U2_HVIT/C-4 (copy 2).wav',
'/media/pi/U2_HVIT/C-8 (copy 2).wav',
'/media/pi/U2_HVIT/D-2 (copy 2).wav',
'/media/pi/U2_HVIT/D-4 (copy 2).wav',
'/media/pi/U2_HVIT/D-8 (copy 2).wav',
'/media/pi/U2_HVIT/E-2 (copy 2).wav',
'/media/pi/U2_HVIT/E-4 (copy 2).wav',
'/media/pi/U2_HVIT/E-8 (copy 2).wav',
'/media/pi/U2_HVIT/F-2 (copy 2).wav',
'/media/pi/U2_HVIT/F-4 (copy 2).wav',
'/media/pi/U2_HVIT/F-8 (copy 2).wav',
'/media/pi/U2_HVIT/G-2 (copy 2).wav',
'/media/pi/U2_HVIT/G-4 (copy 2).wav',
'/media/pi/U2_HVIT/G-8 (copy 2).wav']

dic = dict(zip(keys, files))

charlist = ['b', 'a', 'g', 'f', 'e', 'd', 'c']

ser = serial.Serial('/dev/ttyUSB0', 9600)
pygame.mixer.init(frequency=44100, size=-16, channels=4)

def playSound(noteint):
    sound = pygame.mixer.Sound(noteint)
    chan = pygame.mixer.find_channel()
    chan.queue(sound)
    


while 1:
    #c = 0
    #sounds = []
    line = ser.readline()
    floatline = list(np.fromstring(line, dtype=float, sep=' '))
    print(floatline)
    for t in floatline:
        if t == 2.0:
            playSound(dic[charlist[floatline.index(t)] + '2'])
            #sounds.append(charlist[floatline.index(t)] + '2')
            #c += 1
        elif t == 4.0:
            playSound(dic[charlist[floatline.index(t)] + '4'])
            #sounds.append(charlist[floatline.index(t)] + '4')
            #c += 1
        elif t == 8.0:
            playSound(dic[charlist[floatline.index(t)] + '8'])
            #sounds.append(charlist[floatline.index(t)] + '8')
            #c += 1
    print(sounds)
    print(c)
    #for sound in sounds:
        #playSound(dic[sound])
    
    
    
