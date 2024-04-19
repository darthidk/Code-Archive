import pygame
screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("physics engine")

#gravity stuff
gravity = 1
clock = pygame.time.Clock()
fps = 60

#object
Objectimg = pygame.transform.scale(pygame.image.load(r'Pygame\Images\box.png'), (50, 50))
ObjectX = 400
ObjectY = 0
Objectgrav = 0
Objectstatus = "Moving"
Objectdirection = "None"
airresistance = gravity/fps
Momentum = 0

class Object:
    def __init__(self):
        global ObjectX, ObjectY, Objectgrav, Objectstatus, Objectdirection
        ObjectX = ObjectX + Momentum
        if Momentum < 0:
            Objectdirection = "Left"
        elif Momentum > 0:
            Objectdirection = "Right"
        else: Objectdirection = "None"
        if ObjectY < 550 or Objectgrav != 0:
            ObjectY += gravity + Objectgrav
            if Objectgrav < airresistance * fps * 6:
                Objectgrav += airresistance
            Object.blit()
        if ObjectY >= 550: 
            ObjectY = 550
            Objectgrav = 0
            Objectstatus = "Stationary"
            Object.blit()

        if Objectstatus == "Stationary":
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    Object.jump()
                    Objectstatus = "Moving"

        if Objectstatus == "Moving":
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_DOWN:
                    Object.fall()

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                Object.direction_momentum("Left", "Move")
            elif event.key == pygame.K_RIGHT:
                Object.direction_momentum("Right", "Move")
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT:
                Object.direction_momentum("Left", "Stop")
            if event.key == pygame.K_RIGHT:
                Object.direction_momentum("Right", "Stop")
    def blit():
        screen.blit(Objectimg, (ObjectX, ObjectY))
    def jump():
        global Objectgrav
        if ObjectY == 550:
            Objectgrav = -5
    def fall():
        global Objectgrav 
        Objectgrav += 0.01
    def direction_momentum(Direction, Movement):
        global ObjectX, Momentum, Objectdirection
        if Direction == "Left" and Movement == "Move":
            if Momentum == 0:
                Momentum = -1
            else:
                Momentum -= 0.01
                Objectdirection = "Left"
        elif Direction == "Left" and Movement == "Stop" :
            if Objectdirection == "Left":
                for i in range(3):
                    Momentum += 0.01
                if Momentum >= 0:
                    Momentum = 0
        if Direction == "Right" and Movement == "Move":
            if Momentum == 0:
                Momentum = 1
            else:
                Momentum += 0.01
                Objectdirection = "Right"
        elif Direction == "Right" and Movement == "Stop" :
            if Objectdirection == "Right":
                for i in range(3):
                    Momentum -= 0.01
                if Momentum <= 0:
                    Momentum = 0

#game while loop
game_running = True
while game_running:
    screen.fill((0, 200, 0))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            game_running = False

    Object()

    clock.tick(fps)
    pygame.display.update()