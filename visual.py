import matplotlib.pyplot as plt
from PIL import Image,ImageDraw
import math
import pygame
import time
Width,Height= 7000,3000
Scale = 5
Margin = 500
sWidth, sHeight= (Width+Margin)//Scale , (Height+Margin) //Scale
pygame.init()

screen = pygame.display.set_mode((sWidth,sHeight), pygame.RESIZABLE )
clock = pygame.time.Clock()

def transformed(string : str):
    x,y = string.split()
    x = float(x)//Scale 
    y = (3000-float(y)-300)//Scale
    return (x,y,)
def absolute(string : str):
    x,y = [float(x) for x in string.split()]
    return math.sqrt(x*x + y*y)

print("before")
file = open("output.txt")
print("opened")
land = tuple ([ transformed(point) for point in file.readline().strip("[], \nLand:").split(',')] )
pygame.draw.lines(screen,(100,100,100),False,land)


def takeInput():
    pygame.event.clear()
    pygame.display.flip()
    rotate=[float(x) for x in file.readline().strip('[]\n ,').split(',')]
    power=[float(x)*25 for x in file.readline().strip('[]\n ,').split(',')]
    velocity = tuple ([ absolute(point) for point in file.readline().strip("[], \n").split(',')] )
    position = tuple ([ transformed(point) for point in file.readline().strip("[], \n").split(',')] )
    crashIndex, cost = [int(float(x)) for x in file.readline().split()]
    pygame.draw.lines(screen,(100,10,10),False,position,width=2)

    pygame.draw.circle(screen,pygame.Color('white'),position[crashIndex],1)
    plt.axvline(x=crashIndex)

    font = pygame.font.Font('freesansbold.ttf', 15)
    text = font.render(str(cost), True,pygame.Color('white'))
    textRect = text.get_rect()
    screen.blit(text,position[crashIndex+4])

    plt.plot(rotate)
    plt.plot(power)
    plt.plot(velocity)
    plt.ylabel('some numbers')
    plt.savefig("plot.png")

for i in range(100):
    time.sleep(1)
    takeInput()

pygame.display.flip()
done = False; i=0
while not done and i<1000: 
    time.sleep(0.1); i+=1
    for event in pygame.event.get():
        if event.type == pygame.QUIT: done = True
        if event.type == pygame.KEYDOWN: 
            print("keypressed")
            if event.key == pygame.K_ESCAPE: done =True