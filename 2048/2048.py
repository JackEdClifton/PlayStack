import pygame
import random

pygame.init()


class Colour:
	background = (200, 200, 200)
	tile = (250, 250, 250)
	text = (0, 0, 0)


class Direction:
	left = 0
	right = 1
	up = 2
	down = 3


class Game:
		
	TILE_FONT = pygame.font.SysFont('Comic Sans MS', 30)

	def __init__(self):
		self.window = pygame.display.set_mode((400, 400))
		self.tileGrid = [
			[0, 0, 0, 0],
			[0, 0, 0, 0],
			[0, 0, 0, 0],
			[0, 0, 0, 0]
		]
		self._newTile()

	def _newTile(self) -> bool:
		totalFreeSpaces = 0
				
		for row in self.tileGrid:
			for column in row:
				if column == 0:
					totalFreeSpaces += 1
				
		if totalFreeSpaces == 0:
			return True
				
		while True:
			row = random.randint(0, 3)
			column = random.randint(0, 3)

			if self.tileGrid[row][column]:
				continue
		
			self.tileGrid[row][column] = 2
			return False


	def draw(self) -> None:
		
		for y, row in enumerate(self.tileGrid):
			for x, column in enumerate(row):
				
				pygame.draw.rect(self.window, Colour.tile, (
					5 + 100 * x,
					5 + 100 * y,
					90, 90
				))
				
				if not column:
					continue
				self.window.blit(
					self.TILE_FONT.render(str(column), False, (0, 0, 0)), (
						20 + 100 * x,
						30 + 100 * y
					)
				)


	def moveLeft(self) -> bool:
		self.mergeXAxis()
		
		for y, row in enumerate(self.tileGrid):
			for x in range(3):
				
				while x >= 0:
					
					if row[x] == 0 and row[x+1]:
						self.tileGrid[y][x] = row[x+1]
						self.tileGrid[y][x+1] = 0
					
					x -= 1

		return self._newTile()


	def moveRight(self) -> bool:
		self.mergeXAxis()

		for y, row in enumerate(self.tileGrid):
			for x in range(2, -1, -1):

				while x >= 0:

					if row[x] and row[x+1] == 0:
						self.tileGrid[y][x+1] = row[x]
						self.tileGrid[y][x] = 0

					x -= 1

		return self._newTile()


	def moveUp(self) -> bool:
		self.mergeYAxis()
				
		for x in range(4):
			for y in range(3):

				while y >= 0:

					if self.tileGrid[y][x] == 0 and self.tileGrid[y+1][x]:
						self.tileGrid[y][x] = self.tileGrid[y+1][x]
						self.tileGrid[y+1][x] = 0

					y -= 1

		return self._newTile()


	def moveDown(self) -> bool:
		self.mergeYAxis()

		for x in range(4):
			for y in range(3):

				while y >= 0:

					if self.tileGrid[y][x] and self.tileGrid[y+1][x] == 0:
						self.tileGrid[y+1][x] = self.tileGrid[y][x]
						self.tileGrid[y][x] = 0

					y -= 1

		return self._newTile()

	def mergeXAxis(self):
		for y, row in enumerate(self.tileGrid):
			for x in range(3):
				if row[x] == row[x+1]:
					row[x] *= 2
					row[x+1] = 0

	def mergeYAxis(self):
		for x in range(4):
			for y in range(3):

				if self.tileGrid[y][x] == self.tileGrid[y+1][x]:
					self.tileGrid[y][x] *= 2
					self.tileGrid[y+1][x] = 0


	def move(direction):
		pass

def main():
	game = Game()

	while 1:

		for event in pygame.event.get():

			if event.type == pygame.QUIT:
				quit()

			if event.type == pygame.KEYDOWN:
				if   event.key == pygame.K_LEFT : game.moveLeft()
				elif event.key == pygame.K_RIGHT: game.moveRight()
				elif event.key == pygame.K_UP   : game.moveUp()
				elif event.key == pygame.K_DOWN : game.moveDown()

		game.draw()
		pygame.display.update()
		game.window.fill(Colour.background)



if __name__ == "__main__":
	main()