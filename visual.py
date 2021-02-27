import matplotlib.pyplot as plt
from PIL import Image,ImageDraw
import math,random
import pygame
import time
from visual_helper import randColor,absolute,transformed,Width,Height,Scale,Margin

sWidth, sHeight= (Width+Margin)//Scale , (Height+Margin) //Scale
pygame.init()

screen = pygame.display.set_mode((sWidth,sHeight), pygame.RESIZABLE )
clock = pygame.time.Clock()


file = open("data/output.txt")
data = file.readlines()

popSize = int(data[0])
land = tuple ([ transformed(point) for point in data[1].strip("[], \nLand:").split(',')] )
last_index=2
def screen_reset():
    screen.fill((0,0,0))
    pygame.draw.lines(screen,pygame.Color('white'),False,land)

def draw_individual(num : int):
    start = num*5 + last_index
    rotate=[float(x) for x in data[start].strip('[]\n ,arrRotate=').split(',')]
    power=[float(x)*25 for x in data[start+1].strip('[]\n ,arrPower=').split(',')]
    velocity = tuple ([ absolute(point) for point in data[start+2].strip("[], \n").split(',')] )
    position = tuple ([ transformed(point) for point in data[start+3].strip("[], \n").split(',')] )
    crashIndex, cost = [int(float(x)) for x in data[start+4].split()]


    pygame.draw.lines(screen,randColor(),False,position,width=2)

    pygame.draw.circle(screen,pygame.Color('white'),position[crashIndex],1)
    plt.axvline(x=crashIndex)

    font = pygame.font.Font('freesansbold.ttf', 15)
    text = font.render(str(cost), True,pygame.Color('white'))
    textRect = text.get_rect()
    screen.blit(text,position[crashIndex+4 if crashIndex+4 <len(position) else crashIndex])

    plt.plot(rotate)
    plt.plot(power)
    plt.plot(velocity)
    plt.ylabel('some numbers')
    # saving the figure in a core inner loop... Worst idea ever
    # plt.savefig("data/plot.png") 
    
    pygame.display.flip()
    pygame.event.clear()
    # end drawl_gen

def draw_gen(num: int):
    start = num* popSize
    for i in range(popSize):
        draw_individual(start + i)
    plt.savefig("data/plot.png")

done = False; i=0
num =0
pnum =1
changed =False
while not done and i<1000: 
    time.sleep(0.1); i+=1
    for event in pygame.event.get():
        if event.type == pygame.QUIT: done = True
        if event.type == pygame.KEYDOWN: 
            if event.key == pygame.K_ESCAPE: done =True
            if event.key == pygame.K_RIGHT : num+=1 
            if event.key == pygame.K_LEFT : num -= 1 if num>0 else 0 ; 
            if event.key == pygame.K_d : num+=5 
            if event.key == pygame.K_a : num-=5 if num>5 else 0

    if(num != pnum):
        screen_reset()
        draw_gen(num)
        pnum=num