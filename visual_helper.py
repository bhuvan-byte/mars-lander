import math,random
import time
Width,Height= 7000,3000
Scale = 5
Margin = 500
def transformed(string : str):
    x,y = string.split()
    x = float(x)//Scale 
    y = (3000-float(y)-300)//Scale
    return (x,y,)
def absolute(string : str):
    x,y = [float(x) for x in string.split()]
    return math.sqrt(x*x + y*y)
def randColor():
    return (random.randint(0,255),random.randint(0,255),random.randint(0,255))
# def takeInput():
#     pygame.event.clear()
#     pygame.display.flip()
#     rotate=[float(x) for x in file.readline().strip('[]\n ,').split(',')]
#     power=[float(x)*25 for x in file.readline().strip('[]\n ,').split(',')]
#     velocity = tuple ([ absolute(point) for point in file.readline().strip("[], \n").split(',')] )
#     position = tuple ([ transformed(point) for point in file.readline().strip("[], \n").split(',')] )
#     crashIndex, cost = [int(float(x)) for x in file.readline().split()]
    
#     pygame.draw.lines(screen,randColor(),False,position,width=2)

#     pygame.draw.circle(screen,pygame.Color('white'),position[crashIndex],1)
#     plt.axvline(x=crashIndex)

#     font = pygame.font.Font('freesansbold.ttf', 15)
#     text = font.render(str(cost), True,pygame.Color('white'))
#     textRect = text.get_rect()
#     screen.blit(text,position[crashIndex+4])

#     plt.plot(rotate)
#     plt.plot(power)
#     plt.plot(velocity)
#     plt.ylabel('some numbers')
#     plt.savefig("plot.png")