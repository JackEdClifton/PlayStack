
import pygame
import random
import time

class Collisions:
	def point_within_rect(point, rect):
		return point[0] >= rect[0] and point[0] <= rect[0] + rect[2] and \
			point[1] >= rect[1] and point[1] <= rect[1] + rect[3]

class Grid:
	empty = 0
	full = 1
	flagged = 2

	def __init__(self, width=5, height=5):
		self.width = width
		self.height = height
		self.size = 60
		self.reset_grids()

	def reset_grids(self):
		self.answer_grid = [int(random.randint(0, 99) < 20) for _ in range(self.width*self.height)]
		self.grid = [0 for _ in range(self.width*self.height)]

	def draw(self, surface):
		self.draw_grid(surface)
		self.draw_text(surface)

	def draw_grid(self, surface):
		for y in range(self.height):
			for x in range(self.width):
				current_cell = self.grid[y*self.width + x]
				if current_cell == Grid.empty: colour = (255,255,255)
				elif current_cell == Grid.full: colour = (0,0,0)
				elif current_cell == Grid.flagged: colour = (150,80,80)

				pygame.draw.rect(surface, colour, (
					100+x*self.size,
					100+y*self.size,
					self.size-10,
					self.size-10
				))
	
	def draw_text(self, surface):
		
		font = pygame.font.SysFont("Consolas", 25)
		
		for y in range(self.height):
			text_surface = font.render(self.count_row(y), False, (0, 0, 0))
			surface.blit(text_surface, (50, 110+y*self.size))

		for x in range(self.width):
			text_surface = font.render(self.count_column(x), False, (0, 0, 0))
			surface.blit(text_surface, (100+x*self.size, 70))

	def count_row(self, row):
		return self.count_row_or_column(range(self.width*row, self.width*(row+1)))
	
	def count_column(self, column):
		return self.count_row_or_column(range(column, self.width*self.height, self.width))

	def count_row_or_column(self, range_obj):
		output = ""
		count = 0
		for i in range_obj:
			count += self.answer_grid[i] == Grid.full
			if self.answer_grid[i] != Grid.full:
				if count:
					output += str(count) + " "
					count = 0
		if count:
			output += str(count) + " "
		return output
	
	def handle_click(self, mouse_pos, right_click=False):
		for y in range(self.height):
			for x in range(self.width):
				if Collisions.point_within_rect(mouse_pos,
					(100+x*self.size, 100+y*self.size, self.size-10, self.size-10)):
					index = y*self.width + x
					if right_click:
						self.grid[index] = Grid.empty if self.grid[index] == Grid.flagged else Grid.flagged
					else:
						self.grid[index] = not self.grid[index]
		
		for index in range(self.width*self.height):
			if (self.grid[index] == Grid.full) != (self.answer_grid[index] == Grid.full):
				return
		self.reset_grids()

	
def main():

	# create window
	pygame.init()
	pygame.display.set_caption("Text")
	window = pygame.display.set_mode((400, 400))
	pygame.display.set_caption("Text")

	font = pygame.font.SysFont("Consolas", 30)

	game_clock = pygame.time.Clock()
	start_time = time.time()
	elapsed_time = 0.0
	grid = Grid()

	# start mainloop
	run_mainloop = True
	redraw_frame = True
	while run_mainloop:
		elapsed_time += game_clock.tick(10)
		
		# handle events
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				run_mainloop = False

			if event.type == pygame.MOUSEBUTTONDOWN:
				redraw_frame = True
				if event.button == 1:
					grid.handle_click(pygame.mouse.get_pos())
				else:
					grid.handle_click(pygame.mouse.get_pos(), True)
				

		# draw objects
		if redraw_frame or elapsed_time > 1000.0:
			window.fill((20,120,120))
			grid.draw(window)

			window.blit(font.render(f"FPS: {int(game_clock.get_fps())}", False, (0, 0, 0)), (20, 10))
			window.blit(font.render(f"Time: {int(time.time() - start_time)}", False, (0, 0, 0)), (150, 10))

			pygame.display.update()

			redraw_frame = False
			elapsed_time = 0.0



if __name__ == "__main__":
	main()