import sys
import math

# Save humans, destroy zombies!
class Ash:
	def __init__(self, x, y):
		self.x = x
		self.y = y

	def move(self, x, y):
		self.x = x
		self.y = y

class Human:
	def __init__(self, id, x, y):
		self.id = id
		self.x = x
		self.y = y

class Zombie:
	def __init__(self, id, x, y, nx, ny):
		self.id = id
		self.x = x
		self.y = y
		self.nx = nx
		self.ny = ny

def calc_dist(x1, y1, x2, y2):
	dx = x2 - x1
	dy = y2 - y1
	return math.sqrt((dx*dx) + (dy*dy))

class Actors:
	def __init__(self):
		self.ash = Ash(0, 0)
		self.humans = []
		self.zombies = []

	def new_round(self, ashx, ashy):
		self.ash.move(ashx, ashy)
		self.humans.clear()
		self.zombies.clear()

	def add_human(self, h):
		self.humans.append(h)

	def add_zombie(self, z):
		self.zombies.append(z)

	def get_closest_human(self):
		ret = None
		distance = float("inf")
		for h in self.humans:
			tmp_dist = calc_dist(self.ash.x, self.ash.y, h.x, h.y)
			if (tmp_dist < distance):
				ret = h
				distance = tmp_dist
		return ret

# game loop
actors = Actors()
while True:
	x, y = [int(i) for i in input().split()]
	actors.new_round(x, y)
	human_count = int(input())
	for i in range(human_count):
		human_id, human_x, human_y = [int(j) for j in input().split()]
		h = Human(human_id, human_x, human_y)
		actors.add_human(h)
	zombie_count = int(input())
	for i in range(zombie_count):
		zombie_id, zombie_x, zombie_y, zombie_xnext, zombie_ynext = [int(j) for j in input().split()]
		z = Zombie(zombie_id, zombie_x, zombie_y, zombie_xnext, zombie_ynext)
		actors.add_zombie(z)

	# Fist approach: Try to save the closest human (not always possible)
	h = actors.get_closest_human()

	# Your destination coordinates
	print(str(h.x)+" "+str(h.y))
