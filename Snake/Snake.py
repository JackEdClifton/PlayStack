
# modules
import pygame
import threading
import winsound
import time
from Game import *
from SnakeClass import *

# objects
pygame.init()
game = Game_Class()


def main():

    # mainloop
    while game.run:

        # update display
        pygame.display.update()
        game.display.fill(game.bg)
        game.clock.tick(game.fps)

        # events
        for event in pygame.event.get():

            if event.type == pygame.QUIT:
                game.run = False

            # key is pressed down
            if event.type == pygame.KEYDOWN:
                
                # x axis
                if game.snake.direction in [Direction.up, Direction.down]:
                    if event.key == pygame.K_a:
                        game.snake.direction_queue = Direction.left
                    elif event.key == pygame.K_d:
                        game.snake.direction_queue = Direction.right
                
                # y axis
                if game.snake.direction in [Direction.left, Direction.right]:
                    if event.key == pygame.K_w:
                        game.snake.direction_queue = Direction.up
                    elif event.key == pygame.K_s:
                        game.snake.direction_queue = Direction.down

                # pause
                if event.key == pygame.K_p:
                    game.paused = not game.paused
                if event.key == pygame.K_f:
                    game.toggle_display()

        startT = time.time()

        # draw
        game.draw_map()
        game.draw_hud()
        game.snake.draw()
        game.snake.draw_food()

        print("Time:", time.time() - startT)

        # comment
        if not game.paused:
            game.snake.move()
            game.snake.eat_food()
            game.snake.check_collision()



# run program
if __name__ == "__main__":
    main()
    pygame.quit()
    quit()

