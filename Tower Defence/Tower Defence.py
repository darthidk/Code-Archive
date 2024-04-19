import pygame
import math
from threading import Timer
pygame.init()

#screen
screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("Tower Defence")
background = pygame.image.load(r'Map.png')

#round tracking/text
round = 1
round_status = "Sending"
menu_font = pygame.font.Font('freesansbold.ttf', 32)
def round_text():
    rnd_txt = menu_font.render("Round " + str(round), True, 255)
    if round >= 10:
        screen.blit(rnd_txt, (645, 480))
    else: 
        screen.blit(rnd_txt, (660, 480))

#lives
lives = 50
def lives_text():
    lives_txt = menu_font.render("Lives: " + str(lives), True, 255)
    screen.blit(lives_txt, (650, 520))

#cash text
cash_num = 100
def cash_text():
    cash_txt = menu_font.render("$ " + str(cash_num), True, 255)
    screen.blit(cash_txt, (0, 480))

#game over
game_over_font = pygame.font.Font("freesansbold.ttf", 75)
def game_over():
    game_over_txt = game_over_font.render("Game Over", True, 255)
    screen.blit(game_over_txt, (185, 225))

#red bloons
redbloonimg = []
redX = []
redY = []
redX_change = []
redY_change = []
redY_start = 0
num_of_red = 0
red_spacing = 0

def red_bloon_spawn():
    for i in range(num_of_red):
        global redY_start
        redbloonimg.append(pygame.image.load(r'Red bloon.png'))
        redX.append(117.5)
        redY.append(redY_start)
        redX_change.append(0)
        redY_change.append(0)
        redY_start -= red_spacing

def redfunc(x, y, i):
    screen.blit(redbloonimg[i], (x, y))

#red bloon movement
def red_bloon_move(i):
    global lives
    global totalbloons
    if redX[i] == 117.5:
        if redY[i] <= 0:
            redY_change[i] = 1
    if redX[i] == 117.5:
        if redY[i] >= 312.5:
            redX_change[i] = 1
            redY_change[i] = 0
            redY[i] = 312.5
    if redY[i] == 312.5:
        if redX[i] >= 430:
            redX_change[i] = 1
            redY_change[i] = 0.6
    if redY[i] >= 400:
        if redY[i] < 420:
            redX_change[i] = 1
            redY_change[i] = 0
            redY[i] = 400
    if redX[i] >= 627.5:
        if redY[i] == 400:
            redX_change[i] = 0
            redY_change[i] = -1
            redX[i] = 627.5
    if redY[i] <= 185:
        if redY[i] >= 160:
            if redX[i] == 627.5:
                redX_change[i] = -1
                redY_change[i] = -1
                redY[i] = 185
    if redY[i] <= 100:
        if redY[i] >= 90:
            if redX[i] >= 525.5: 
                redY_change[i] = 0
                redX_change[i] = -1
                redY[i] = 100
    if redX[i] <= 362.5:
        if redX[i] >= 360:
            if redY[i] == 100:
                redY_change[i] = -1
                redX_change[i] = 0
                redX[i] = 362.5
    if redY[i] <= 25:
        if redX[i] == 362.5:
            redX_change[i] = 1
            redY_change[i] = 0
    if redX[i] >= 800:
        if redX[i] <= 810:
            lives -= 1
            redX[i] = 900
            redX_change[i] = 0
            totalbloons -= 1

#blue bloons
bluebloonimg = []
blueX = []
blueY = []
blueX_change = []
blueY_change = []
blueY_start = 0
num_of_blue = 0
blue_spacing = 0

def blue_bloon_spawn():
    for i in range(num_of_blue):
        global blueY_start
        bluebloonimg.append(pygame.image.load(r'Blue bloon.png'))
        blueX.append(117.5)
        blueY.append(blueY_start)
        blueX_change.append(0)
        blueY_change.append(0)
        blueY_start -= blue_spacing

def bluefunc(x, y, i):
    screen.blit(bluebloonimg[i], (x, y))

#blue bloon movement
def blue_bloon_move(i):
    global blueX_change
    global blueY_change
    global blueY
    global blueX 
    global lives
    global totalbloons
    if blueX[i] == 117.5:
        if blueY[i] <= 0:
            blueY_change[i] = 1.1
    if blueX[i] == 117.5:
        if blueY[i] >= 312.5:
            blueX_change[i] = 1.1
            blueY_change[i] = 0
            blueY[i] = 312.5
    if blueY[i] == 312.5:
        if blueX[i] >= 430:
            blueX_change[i] = 1.1
            blueY_change[i] = 0.65
    if blueY[i] >= 400:
        if blueY[i] < 420:
            blueX_change[i] = 1.1
            blueY_change[i] = 0
            blueY[i] = 400
    if blueX[i] >= 627.5:
        if blueY[i] == 400:
            blueX_change[i] = 0
            blueY_change[i] = -1.1
            blueX[i] = 627.5
    if blueY[i] <= 185:
        if blueY[i] >= 160:
            if blueX[i] == 627.5:
                blueX_change[i] = -1.1
                blueY_change[i] = -1.1
                blueY[i] = 185
    if blueY[i] <= 100:
        if blueY[i] >= 90:
            if blueX[i] >= 525.5: 
                blueY_change[i] = 0
                blueX_change[i] = -1.1
                blueY[i] = 100
    if blueX[i] <= 362.5:
        if blueX[i] >= 360:
            if blueY[i] == 100:
                blueY_change[i] = -1.1
                blueX_change[i] = 0
                blueX[i] = 362.5
    if blueY[i] <= 25:
        if blueX[i] == 362.5:
            blueX_change[i] = 1.1
            blueY_change[i] = 0
            blueY[i] == 25
    if blueX[i] >= 800:
        if blueX[i] <= 810:
            lives -= 2
            blueX[i] = 900
            blueX_change[i] = 0
            totalbloons -= 2

#green bloons
greenbloonimg = []
greenX = []
greenY = []
greenX_change = []
greenY_change = []
greenY_start = 0
num_of_green = 0
green_spacing = 0

def green_bloon_spawn():
    for i in range(num_of_green):
        global greenY_start
        greenbloonimg.append(pygame.image.load(r'Green bloon.png'))
        greenX.append(117.5)
        greenY.append(greenY_start)
        greenX_change.append(0)
        greenY_change.append(0)
        greenY_start -= green_spacing

def greenfunc(x, y, i):
    screen.blit(greenbloonimg[i], (x, y))

#class bloon movement
class BloonMovement:
    def __init__(self, colour, i):
        x = int()
        y = int()
        x_change = int()
        y_change = int()
        bloon_active = True
        if colour == "red":
            totalhealth = 1
            speed = 1
        elif colour == "blue":
            totalhealth = 2
            speed = 1.1
            def bloon_update():
                blueX[i] = x
                blueY[i] = y
                blueX_change[i] = x_change
                blueY_change[i] = y_change
        elif colour == "green":
            totalhealth = 3
            speed = 1.2
            def bloon_update(self):
                greenX[i] = x
                greenY[i] = y
                greenX_change[i] = x_change
                greenY_change[i] = y_change
            def bloon_var_update(self):
                x = greenX[i]
                y = greenY[i]
        if x == 117.5:
            if y <= 0:
                y_change = 1 * speed
                bloon_update()
        if x == 117.5:
            if y >= 312.5:
                x_change = 1 * speed
                y_change = 0
                y = 312.5
                bloon_update()
        if y == 312.5:
            if x >= 430:
                x_change = 1 * speed
                y_change = 0.6 * speed
        if y >= 400:
                x_change = 1 * speed
                y_change = 0
                y = 400
        if x >= 627.5:
            if y == 400:
                x_change = 0
                y_change = -1 * speed
                x = 627.5
        if y <= 185:
            if y >= 160:
                if x == 627.5:
                    x_change = -1 * speed
                    y_change = -1 * speed
                    y = 185
        if y <= 100:
            if y >= 90:
                if x >= 525.5: 
                    y_change = 0
                    x_change = -1 * speed
                    y = 100
        if x <= 362.5:
            if x >= 360:
                if y == 100:
                    y_change = -1 * speed 
                    x_change = 0
                    x = 362.5
        if y <= 25:
            if x == 362.5:
                x_change = 1
                y_change = 0
        if x >= 800:
            if x <= 810:
                global lives
                global totalbloons
                lives -= totalhealth
                x = 900
                x_change = 0
                totalbloons -= totalhealth

#machine gunner
machinegunnerimg = pygame.image.load(r'machinegun1.png')
mach_gunnerX = 200
mach_gunnerY = 250

#bullet
bulletimg = pygame.image.load(r'bullet.png')
bulletX = 900
bulletY = 900
bulletX_change = 0
bulletY_change = 0
bullet_state = "Ready"
bloon_in_range = []

#class for all machine gunner functions
class MachGunnerFire:  
    def towerblit(x, y):
        screen.blit(machinegunnerimg, (x, y))
    def rangecalc(bloonX, bloonY, i, colour):
        #is only triggering for the first bloon
        distance = math.sqrt(math.pow((bloonX+20)-(mach_gunnerX+25), 2)) + math.sqrt(math.pow((bloonY+25)-(mach_gunnerY+13), 2))
        if distance <= 150:
            x_distance = math.sqrt(math.pow((bloonX+20)-(mach_gunnerX+25), 2)) + math.sqrt(math.pow((mach_gunnerY+13)-(mach_gunnerY+13), 2))
            y_distance = math.sqrt(math.pow((mach_gunnerX+25)-(mach_gunnerX+25), 2)) + math.sqrt(math.pow((bloonY+20)-(mach_gunnerY+13), 2))
            #send bulletcalc here
            # if len(bloon_in_range) == 0:
            #     bloon_in_range.append((colour, i))
            #     #print(colour, i, 1)
            # elif len(bloon_in_range) == 1:
            #     if bloon_in_range[0] == (colour, i):
            #         #print(colour, i, 2)
            # elif len(bloon_in_range) == 2:
            #     if bloon_in_range[0] == (colour, i):
            #         #print(colour, i, 2, 1)
            #     if bloon_in_range[0] == (colour, i):
            #         #print(colour, i, 2, 3)
            # elif len(bloon_in_range) > 2:
            #     for j in range(len(bloon_in_range) - 1):
            #         if bloon_in_range[j] == (colour, i):
            #             #print(colour, i, 3)
            # else:
            #     bloon_in_range.append((colour, i))
            #     #print(colour, i, 4)
        elif distance > 10000:
            #print(colour, i, 5)
            for j in range(len(bloon_in_range)):
                try:
                    if bloon_in_range[j] == (colour, i):
                        bloon_in_range.pop(j)
                except IndexError:
                    pass 
    def bulletcalc(distance, x_distance, y_distance, bloonX, bloonY):
        global bullet_state
        if bullet_state == "Ready":
            bullet_state = "Firing"
            angle = math.degrees(math.acos(x_distance/distance))
            if bloonY <= mach_gunnerY: 
                if bloonX >= mach_gunnerX:
                    quadrant = 1
                    x_side = "Pos"
                    y_side = "Neg"
                elif bloonX < mach_gunnerX:
                    quadrant = 2
                    x_side = "Neg"
                    y_side = "Neg"
            elif bloonY > mach_gunnerY: 
                if bloonX <= mach_gunnerX:
                    quadrant = 3
                    x_side = "Neg"
                    y_side = "Pos"
                elif bloonX > mach_gunnerX: 
                    quadrant = 4
                    x_side = "Pos"
                    y_side = "Pos" 
            if y_distance < 50:
                angle = (90 * quadrant) - angle
            elif quadrant == 4:
                if angle > 45:
                    angle = 90 - angle
                    angle += (90 * (quadrant - 1)) + 15
            else:
                angle = (90 * (quadrant - 1)) + angle
            global rotated_bullet
            rotated_bullet = pygame.transform.rotate(bulletimg, angle)
            global bulletX_change
            global bulletY_change
            if x_side == "Neg":
                bulletX_change = -x_distance / 8
            else:
                bulletX_change = x_distance / 8
            if y_side == "Neg":
                bulletY_change = -y_distance / 8
            else:
                bulletY_change = y_distance / 8
            global bulletX
            global bulletY
            bulletX = 200
            bulletY = 250
            MachGunnerFire.bulletblit(rotated_bullet, bulletX, bulletY)
            bullet_state = "Fired"
    def bulletblit(img, x, y):
        screen.blit(img, (x, y))
    def cooldown():
        global bullet_state
        bullet_state = "Cooldown"
        def cooldown_func():
            global bullet_state
            bullet_state = "Ready"
        t = Timer(2.5, cooldown_func)
        t.start()
    def firing():
        global bulletX
        global bulletY
        global bulletX_change
        global bulletY_change
        if bullet_state == "Fired":
            MachGunnerFire.bulletblit(rotated_bullet, bulletX, bulletY)
            if bulletX < 800:
                if bulletY < 600:
                    bullet_travel = math.sqrt(math.pow((bulletX+12.5)-(mach_gunnerX+25), 2)) + math.sqrt(math.pow((bulletY+6.5)-(mach_gunnerY+13), 2))
                    if bullet_travel > 150:
                        bulletX = 900
                        bulletY = 900
                        bulletX_change = 0
                        bulletY_change = 0
                        MachGunnerFire.cooldown()
                elif bulletY > 600:
                    bulletX = 900
                    bulletY = 900
                    bulletX_change = 0
                    bulletY_change = 0
            elif bulletX > 800:
                bulletX = 900
                bulletY = 900
                bulletX_change = 0
                bulletY_change = 0
            

#collision detection/bullet hitting bloon
def collision(bulletX1, bulletY1, X, Y, i, colour):
    if bullet_state == "Fired":
        distance = math.sqrt(math.pow((X+20)-(bulletX1+12.5), 2)) + math.sqrt(math.pow((Y+25)-(bulletY1+5), 2))
        if distance < 25:
            global totalbloons
            global num_of_red
            global cash_num
            global bulletX
            global bulletY
            bulletX = 900
            bulletY = 900
            MachGunnerFire.cooldown()
            if colour == "red":
                totalbloons -= 1
                redX_change[i] = 0
                redY_change[i] = 0
                redX[i] = 900
                redY[i] = 900
                cash_num += 1
            if colour == "blue":
                k = len(redX)
                redbloonimg.append(pygame.image.load(r'Tower Defence\Red bloon.png'))
                redX.append(X)
                redY.append(Y)
                newX_change = 0
                newY_change = 0
                if blueX_change[i] > 0:
                    newX_change = blueX_change[i] - 0.1
                    redX[k] -= 20
                elif blueX_change[i] < 0: 
                    newX_change = blueX_change[i] + 0.1
                    redX[k] += 20
                if blueY_change[i] > 0:
                    newY_change = blueY_change[i] - 0.1
                    redY[k] -= 20
                elif blueY_change[i] < 0:
                    newY_change = blueY_change[i] + 0.1
                    redY[k] += 20
                
                redX_change.append(newX_change)
                redY_change.append(newY_change)
                num_of_red += 1

                blueX[i] = 900
                blueX[i] = 900
                blueX_change[i] = 0
                blueY_change[i] = 0 
                
                totalbloons -= 1
                cash_num += 1

#round tracking/triggering next round
totalbloons = 0
bloon_distance_tracking = []

def total_bloon_func():
    global totalbloons
    if totalbloons == 0:
        global round
        global round_status
        round += 1
        round_status = "Sending"
        round_send()
        total_bloon_calc()

def total_bloon_calc():
    global totalbloons
    global num_of_red
    global num_of_blue
    global num_of_green
    totalbloons = num_of_red + (num_of_blue * 2) + (num_of_green * 3)


#round creation
def round_send():
    global round_status
    global num_of_red
    global redY_start
    global red_spacing
    global num_of_blue
    global blueY_start
    global blue_spacing
    global num_of_green
    global greenY_start
    global green_spacing
    if round_status == "Sending":
        if round == 1:
            bloon_reset()
            num_of_red = 0
            redY_start = 0
            red_spacing = 50
            num_of_blue = 5
            blueY_start = -250
            blue_spacing = 450
            bloon_spawn()
        if round == 2:
            bloon_reset()
            num_of_red = 10
            red_spacing = 50
            redY_start = 0
            num_of_blue = 10
            blueY_start = -200
            blue_spacing = 25
            bloon_spawn()
        if round == 3:
            bloon_reset()
            num_of_red = 10
            red_spacing = 100
            redY_start = 0
            num_of_blue = 5 
            blueY_start = -950
            blue_spacing = 100
            bloon_spawn()
        if round == 4:
            bloon_reset()
            num_of_blue = 2
            blueY_start = 0
            blue_spacing = 40
            bloon_spawn()
        for i in range(num_of_red):
            bloon_distance_tracking.append(redY[i])
        for i in range(num_of_blue):
            bloon_distance_tracking.append(blueY[i])
        for i in range(num_of_green):
            bloon_distance_tracking.append(greenY[i])

def bloon_reset():
    global redY_start
    global blueY_start
    global greenY_start
    redbloonimg.clear()
    redX.clear()
    redY.clear()
    redX_change.clear()
    redY_change.clear()
    redY_start = 0

    bluebloonimg.clear()
    blueX.clear()
    blueY.clear()
    blueX_change.clear()
    blueY_change.clear()
    blueY_start = 0

    greenbloonimg.clear()
    greenX.clear()
    greenY.clear()
    greenX_change.clear()
    greenY_change.clear()
    greenY_start = 0

    bloon_distance_tracking.clear()

def bloon_spawn():
    red_bloon_spawn()
    blue_bloon_spawn()
    green_bloon_spawn()
    total_bloon_calc()
    global round_status
    round_status = "Sent"


#while loop
running = True
while running:
    screen.fill((0, 0, 0))
    screen.blit(background, (0, 0))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    #red bloon movement
    for i in range(num_of_red):
        redX[i] += redX_change[i]
        redY[i] += redY_change[i]
        redfunc(redX[i], redY[i], i)
        red_bloon_move(i)
        MachGunnerFire.rangecalc(redX[i], redY[i], i, "Red")
        collision(bulletX, bulletY, redX[i], redY[i], i, "red")

    #blue bloon movement
    for i in range(num_of_blue):
        blueX[i] += blueX_change[i]
        blueY[i] += blueY_change[i]
        bluefunc(blueX[i], blueY[i], i)
        blue_bloon_move(i)
        MachGunnerFire.rangecalc(blueX[i], blueY[i], i, "Blue")
        collision(bulletX, bulletY, blueX[i], blueY[i], i, "blue")

    #green bloon movement
    for i in range(num_of_green):
        greenX[i] += greenX_change[i]
        greenY[i] += greenY_change[i]
        greenfunc(greenX[i], greenY[i], i)
        BloonMovement("green", i)
    
    for i in range(len(bloon_distance_tracking)):
        bloon_distance_tracking[i] += 1

    #bullet movement and firing
    bulletX += bulletX_change
    bulletY += bulletY_change
    MachGunnerFire.firing()
    MachGunnerFire.towerblit(mach_gunnerX, mach_gunnerY)
    #print(bloon_in_range)

    if lives <= 0: 
        lives = 0
        game_over()

    round_send()
    total_bloon_func()
    cash_text()
    round_text()
    lives_text()
    pygame.display.update()
