#starting pygame/random
import pygame
import math
from random import randint as randint
pygame.init()
#screen, name and icon
screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("First Python Game")
image = pygame.image.load(r'Images\Deathtroopersmall.png')
pygame.display.set_icon(image)
game_status = "active"
game_round = 1

#player
playerimg = pygame.image.load(r'Images\legodeathtrooper.jpg')
playerX = 275
playerY = 350
playerX_change = 0
playerY_change = 0
def player(x, y):
    screen.blit(playerimg, (x, y))

#enemy
enemyimg = []
enemyX = []
enemyY = []
enemyX_change = []
enemyY_change = []
num_enemy = 6

for i in range(num_enemy):
    enemyimg.append(pygame.image.load(r'Images\Deathtroopersmall.png'))
    enemyX.append(randint(32, 768))
    enemyY.append(randint(32, 175))
    def direction():
        x = randint(1, 2)
        if x == 1: 
            return -(randint(75, 200))/1000
        elif x == 2:
            return randint(75, 200)/1000
    enemyX_change.append(direction())
    enemyY_change.append(40)

def enemy(x, y, i):
    screen.blit(enemyimg[i], (x, y))

#bullet
bulletimg = pygame.image.load(r'Images\bullet.jpg')
bulletX = 900
bulletY = 900
bulletY_change = 0.5
bullet_state = "ready"
def fire_bullet(x, y):  
    global bullet_state
    bullet_state = "fire"
    screen.blit(bulletimg, (x, y))

#collision function
def iscollision(enemyX, enemyY, bulletX, bulletY):   
    distance = math.sqrt(math.pow(enemyX-bulletX, 2)) + math.sqrt(math.pow(enemyY-bulletY, 2))
    if distance < 48: 
        return True
    else: 
        return False

#score
score_value = 0
font = pygame.font.Font('freesansbold.ttf', 32)
textX = 10
textY = 10
def show_score(x, y):
    score = font.render("Score: " + str(score_value), True, (255, 255, 255))
    screen.blit(score, (x, y))

#high score
open_high_score = open('spaceinvaderscore.txt', "r")
high_score = int(open_high_score.readline())
open_high_score.close()
high_font = pygame.font.Font('freesansbold.ttf', 32)
hightextX = 10
hightextY = 40
def show_high(x, y):
    high_score_text = high_font.render("High Score: " + str(high_score), True, (255, 255, 255))
    screen.blit(high_score_text, (x, y))

#game over text
over_font = pygame.font.Font('freesansbold.ttf', 64)
def game_over_text():
    over_text = over_font.render("Game over", True, (255, 255, 255))
    screen.blit(over_text, (200, 250))



#while loop
running = True
while running:
    screen.fill((1, 155, 1))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            store_score = open('spaceinvaderscore.txt', "r")
            x = store_score.readline()
            print(x)
            if int(x) < high_score:
                store_score.close()
                write_score = open('spaceinvaderscore.txt', "w")
                write_score.write(str(high_score))
                write_score.close()
            else:
                store_score.close()
            running = False
    
    if score_value > high_score:
        high_score = score_value
    #not working
    if event.type == pygame.KEYDOWN:
        if event.key == pygame.K_LSHIFT:
            del_score = open('spaceinvaderscore.txt', "w")
            del_score.write("0")
            del_score.close()

    if game_status == "game over":
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_BACKSPACE:
                game_round += 1
                game_status = "active"
                enemyimg = []
                enemyX = []
                enemyY = []
                enemyX_change = []
                enemyY_change = []
                num_enemy = 6

                for i in range(num_enemy):
                    enemyimg.append(pygame.image.load(r'\Images\Deathtroopersmall.png'))
                    enemyX.append(randint(32, 768))
                    enemyY.append(randint(32, 250))
                    enemyX_change.append(direction())
                    enemyY_change.append(40)
                playerX = 275
                playerY = 300
                bulletY = 900
                score_value = 0
    
    #player x axis
    if event.type == pygame.KEYDOWN:
        if event.key == pygame.K_LEFT:
            playerX_change = -0.1
        if event.key == pygame.K_RIGHT:
            playerX_change = 0.1
    if event.type == pygame.KEYUP:
        if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
            playerX_change = 0

    playerX += playerX_change
    if playerX <= 0:
        playerX = 0
    elif playerX >= 590:
        playerX = 590

    #player y axis
    if event.type == pygame.KEYDOWN:
        if event.key == pygame.K_UP:
            playerY_change = -0.1
        if event.key == pygame.K_DOWN:
            playerY_change = 0.1
    if event.type == pygame.KEYUP:
        if event.key == pygame.K_UP or event.key == pygame.K_DOWN:
            playerY_change = 0
    
    #player movement 
    playerY += playerY_change
    if playerY <= 250:
        playerY = 250
    elif playerY >= 360:
        playerY = 360

    #bullet fire
    if event.type == pygame.KEYDOWN:
        if event.key == pygame.K_LSHIFT:
            if bullet_state == "ready":
                bulletX = playerX
                bulletY = playerY
                fire_bullet(bulletX, bulletY)
    
    #bullet movement
    if bulletY <= -120:
        bulletY = 900
        bullet_state = "ready"
    if bullet_state == "fire":
        fire_bullet(bulletX, bulletY)
        bulletY -= bulletY_change   
    
    #enemy movement
    for i in range(num_enemy):
        #game over
        if enemyY[i] > 300:
            for j in range(num_enemy):
                enemyY[j] = 2000
            game_over_text()
            game_status = "game over"
        enemyX[i] += enemyX_change[i]
        if enemyX[i] <= 0:
            enemyX_change[i] = 0.15
            enemyY[i] += enemyY_change[i]
        elif enemyX[i] >= 768:
            enemyX_change[i] = -0.15
            enemyY[i] += enemyY_change[i]
        collision = iscollision(enemyX[i], enemyY[i], bulletX, bulletY)
        
        #collision
        if collision:
            bulletY = 480
            bullet_state = "ready"
            score_value += 1
            enemyX[i] = randint(32, 768)
            enemyY[i] = randint(32, 175)
            direction()
        enemy(enemyX[i], enemyY[i], i)

    #locations of objects
    show_high(hightextX, hightextY)
    show_score(textX, textY)
    player(playerX, playerY)
    pygame.display.update()