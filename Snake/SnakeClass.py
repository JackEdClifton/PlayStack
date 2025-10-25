
# modules
import pygame; pygame.init()
import random

# enum for directions
class Direction:
    up = 0
    down = 1
    left = 2
    right = 4

# class for snake object
class Snake:

    # constructor
    def __init__(self, display):
        self.display = display

    # setup game for playing
    def reset_game(self):

        # reset snake
        self.length = 1
        self.position = []

        # add starting snake shape
        [self.position.append((x,260)) for x in range(40,81,2)]

        # reset controls
        self.direction = Direction.right
        self.direction_queue = Direction.right
        self.direction_index = 0

        # reset world
        self.spawn_food()
        self.extend_by = 0
        self.colliding = 0


    # draw snake object to window
    def draw(self):
        for body in self.position:
            pygame.draw.circle(self.display, (30,50,140), body, 10)

    
    # move all elements in list
    def move(self):

        # remove tail of snake
        if self.extend_by == 0:
            self.position.pop(0)
        else:
            self.extend_by -= 1
        
        # move snake head
        x, y = self.position[-1]
        if self.direction == Direction.left: x -= 2
        if self.direction == Direction.right: x += 2
        if self.direction == Direction.up: y -= 2
        if self.direction == Direction.down: y += 2

        # add new head of snake
        self.position.append((x,y))

        # increment sub-square
        self.direction_index += 1

        # change direction if not between squares
        if self.direction_index == 10:
            self.direction = self.direction_queue
            self.direction_index = 0
    
    
    # spawn new food object
    def spawn_food(self):
        x = random.choice(range(20,581,20))
        y = random.choice(range(80,521, 20))

        self.food_position = (x,y)
    
    
    # draw food object to window
    def draw_food(self):
        pygame.draw.circle(self.display, (180,40,40), (self.food_position), 8)
    

    # extend snake and respawn food
    def eat_food(self):
        head = self.position[-1]
        if head == self.food_position:
            self.spawn_food()
            self.length += 1
            self.extend_by += 5
    

    # check if snake colliding with food
    def check_collision(self):

        self.colliding = 0
        head = self.position[-1]
        
        # collide with it self
        for body in self.position[:-1]:
            if body == head:
                self.colliding = True

        # collide with wall
        if not(head[0] in range (20,581) and head[1] in range(70,590)):
            self.colliding += 1



