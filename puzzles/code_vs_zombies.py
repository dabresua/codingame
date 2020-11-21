import sys
import math

ASH_SPEED = 1000
ZOMBIE_SPEED = 400
INT_INF = 10000

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
		self.alive = INT_INF
		self.to_reach = INT_INF
		self.priority = INT_INF

	def set_alive(self, zombie_turns):
		self.alive = math.floor(zombie_turns)

	def set_distance(self, ash_turns):
		self.to_reach = math.floor(ash_turns)

	def update_priority(self):
		self.priority = self.alive - self.to_reach
		if (self.priority < 0):
			self.priority = INT_INF

	def debug(self):
		print("["+str(self.x)+" "+str(self.y)+"] "+str(self.priority), file=sys.stderr, flush=True)

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

	def update_humans(self):
		for h in self.humans:
			closest_zombie = None
			distance = float("inf")
			for z in self.zombies:
				tmp_dist = calc_dist(h.x, h.y, z.x, z.y)
				if (tmp_dist < distance):
					closest_zombie = z
					distance = tmp_dist
			h.set_alive(distance/ZOMBIE_SPEED)
			tmp_dist = calc_dist(h.x, h.y, self.ash.x, self.ash.y)
			h.set_distance(tmp_dist/ASH_SPEED-1)
			h.update_priority()
			h.debug()

	def get_most_prioritary(self):
		ret = Human(0,0,0)
		for h in self.humans:
			if (h.priority < ret.priority):
				ret = h
		return ret

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
	#h = actors.get_closest_human()

	# Second approach: Sort the humans for priority and save th most prioritary
	actors.update_humans()
	h = actors.get_most_prioritary()

	# Your destination coordinates
	print(str(h.x)+" "+str(h.y))
