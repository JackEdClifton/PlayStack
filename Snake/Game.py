
# modules
import pygame; pygame.init()
from SnakeClass import Snake
from time import sleep
from threading import Thread

class Game_Class:

    # constructor
    def __init__(self):

        # setup window object
        self.res = (600,600)
        self.display = pygame.display.set_mode(self.res)

        # window attributes
        self.fps = 60
        self.fullscreen = False
        self.bg = (100,120,200)
        self.run = True
        self.paused = False

        # program timer
        self.clock = pygame.time.Clock()
        self.time_elasped = ("00","00")
        Thread(target=self.run_time).start()

        # setup snake object
        self.snake = Snake(self.display)
        self.snake.reset_game()

        # setup font object
        self.font = pygame.font.Font("freesansbold.ttf", 32)



    # toggle between fullscreen and windowed
    def toggle_display(self):
        self.fullscreen = not self.fullscreen
        if self.fullscreen:
            self.display = pygame.display.set_mode(self.res)
        else:
            self.display = pygame.display.set_mode(self.res, pygame.FULLSCREEN)


    # draw map to window
    def draw_map(self):

        # draw map background
        border = 3
        pygame.draw.rect(self.display, (0,50,0), (
                10 - border,       # x position
                70 - border,       # y position
                580 + border * 2,  # width
                520 + border * 2   # height
            )
        )

        # map colours
        colours = [
            (90,170,90),    # dark green
            (150,200,150),  # light green
        ]

        # not a clue what this does
        for y in range(26):

            if y % 2 == 0: index = False
            else: index = True

            for x in range(29):
                x_pos = 20*x + 10
                y_pos = 20*y + 70

                pygame.draw.rect(self.display, colours[index], (x_pos,y_pos,20,20))
                index = not index


    # draw score, time, and dimming
    def draw_hud(self):
        
        # draw score
        score = self.font.render("Score: "+str(self.snake.length), True, (0,0,0))
        self.display.blit(score, (10,10))

        # draw timer
        time =  self.font.render("Time: "+":".join(self.time_elasped), True, (0,0,0))
        self.display.blit(time, (400,0))

        # dim screen if paused
        if self.paused:
            self.dim_screen()

        # dim screen and respawn if died
        if self.snake.colliding:
            self.dim_screen()
            pygame.display.update()
            sleep(1)
            self.snake.reset_game()
    
    
    # async timer of program runtime duration
    def run_time(self):
        m, s = self.time_elasped
        while True:
            # add a second
            m = int(m)
            s = int(s)
            s += 1

            # add a minute if needed
            if s == 60:
                m += 1
                s = 0

            # make length of 'seconds' 2 characters
            if s < 10:
                s = f"0{str(s)}"

            # update time
            self.time_elasped = (str(m),str(s))
            sleep(1)

            # dont increment while game is paused
            while self.paused:
                sleep(0.05)


    # make screen darker if paused or dead
    def dim_screen(self):
        fade = pygame.Surface(self.res)
        fade.fill((0,0,0))
        fade.set_alpha(100)
        self.display.blit(fade, (0,0))
