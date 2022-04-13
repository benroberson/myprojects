#python3
#GRAPHICS TEST: PONG GAME
import pygame, sys, time
from pygame.locals import *
#COMMENT YOUR CODE DANGIT
pygame.init()
#board size
xmax=1000
ymax=700
#open board
DISPLAYSURF = pygame.display.set_mode((xmax, ymax))
pygame.display.set_caption('First Graphics Test')

#colors
BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
RED = (255,   0,   0)
GREEN = (  0, 255,   0)
BLUE = (  0,   0, 255)

FPS=60
fpsClock=pygame.time.Clock()

#puck size
x=200
y=150
w=100
h=50
#paddle size
pw=200
ph=30
px=xmax/2-pw/2
py=ymax-ph
#x and y speed
if len(sys.argv)>=2:
	x_speed=int(sys.argv[1])
	y_speed=int(sys.argv[1])
else:
#default speed
	x_speed=4
	y_speed=4
Ball=pygame.draw.rect(DISPLAYSURF, RED, (x, y, w, h))
paddle=pygame.draw.rect(DISPLAYSURF, WHITE, (px, py, pw, ph))
score = 0

def quitgame():
	print("score:",score)
	pygame.quit()
	sys.exit()

while True: # main game loop
	#puck
	Ball = pygame.Rect((x, y, w, h))
	#erase Ball, paddle
	pygame.draw.rect(DISPLAYSURF, BLACK, Ball)
	pygame.draw.rect(DISPLAYSURF, BLACK, paddle)
	#collisions:
	#left/right wall
	if Ball.right+x_speed > xmax:
		x_speed *= -1
	if x+x_speed < 0:
		x_speed *= -1
	#hitting paddle
	#when Ball is above paddle
	if Ball.bottom+y_speed > ymax-ph:
		#flip y-speed if inside paddle
		if Ball.left<paddle.right and Ball.right>paddle.left:
			y_speed *= -1
			score+=1
	#hitting top
	if y+y_speed < 0:
		y_speed *= -1
	#failed to hit Ball
	if Ball.bottom > ymax:
		time.sleep(0.5)
		quitgame()
	#advance position
	x+=x_speed
	y+=y_speed
	
	#keyboard inputs
	if pygame.key.get_pressed()[K_LEFT] == True:
		paddle.left-=5
	if pygame.key.get_pressed()[K_RIGHT] == True:
		paddle.left+=5
		
	#default quit?
	for event in pygame.event.get():
		if event.type == QUIT:
			quitgame()
	#draw Ball, paddle
	pygame.draw.rect(DISPLAYSURF, RED, (x, y, w, h))
	pygame.draw.rect(DISPLAYSURF, (150,150,150), paddle)
	pygame.display.update()
	fpsClock.tick(FPS)