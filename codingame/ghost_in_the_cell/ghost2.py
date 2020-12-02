import sys
import math

PLAYER = 1
NEUTRAL = 0
ADVERSARY = -1

TROOP_MIN = 0
TROOP_STAY = 0
MIN_POINTS = 5

def owner2str(own):
	if (own == PLAYER):
		return "player"
	if (own == NEUTRAL):
		return "neutral"
	if (own == ADVERSARY):
		return "enemy"
	return "ukn"

def debug(msg):
	print(msg, file=sys.stderr, flush=True)

class Factory:
	def __init__(self, id):
		self.id = id
		self.owner = 0
		self.troops = 0
		self.prod = 0

	def debug(self):
		debug(str(self.id)+"\t"+owner2str(self.owner)+"\t"+str(self.troops)+"\t"+str(self.prod))

class Map:
	def __init__(self, size):
		self.factories = []
		self.size = size
		for x in range(size):
			self.factories.append(Factory(x))
		self.distances = [[0 for x in range(size)] for y in range(size)]

	def set_distance(self, x, y, d):
		self.distances[x][y] = d

	def check_distances(self):
		for x in range(self.size):
			assert self.distances[x][x] == 0

	def update_map(self, data):
		if (data[1] == "FACTORY"):
			id = int(data[0])
			self.factories[id].owner = int(data[2])
			self.factories[id].troops = int(data[3])
			self.factories[id].prod = int(data[4])
			# arg_4 = int(data[5]) ¿¿??
			# arg_5 = int(data[6]) ¿¿??
		elif (data[1] == "TROOP" and int(data[2]) == ADVERSARY):
			debug(data)
			src = int(data[3])
			dst = int(data[4])
			num = int(data[5])
		elif (data[1] == "BOMB" and int(data[2]) == ADVERSARY):
			debug(data)


	def debug(self):
		#debug("--- distances ---")
		#for i in range(self.size):
		#	for j in range(self.size):
		#		print(self.distances[i][j],end = "\t", file=sys.stderr, flush=True)
		#	debug("")
		debug("--- factories ---")
		print("id\towner\ttroops\tprod", file=sys.stderr, flush=True)
		for i in range(self.size):
			self.factories[i].debug()

	def act(self):
		moves = []
		for i in range(self.size):
			moves_f = []
			for j in range(self.size):
				tmp_move = self.Move(self.factories[i], self.factories[j], self.distances[i][j])
				#tmp_move.debug()
				if (tmp_move.points > MIN_POINTS):
					moves_f.append(tmp_move)
			acu = 0
			for m in moves_f:
				acu = acu + m.send
			debug("acu "+str(acu))
			moves_f.sort(key=lambda x: x.points, reverse=True)
			acu = 0
			for m in moves_f:
				acu = acu + m.send
				if (acu < self.factories[i].troops):
					moves.append(m)
					debug("appending :")
					m.debug()

		#move.debug()
		sent = 0
		cmd = ""
		for m in moves:
			if (sent == 1):
				cmd = cmd + ";"
			cmd = cmd + m.getcmd()
			sent = 1
		if (sent == 0):
			print("WAIT")
		else:
			print(cmd)

	class Move:
		# What move should we do next?
		def __init__(self, f1, f2, d):
			self.src = f1.id
			self.dst = f2.id
			self.prod = f1.prod
			self.troops = f1.troops
			troops_then = f2.prod
			if (f2.owner == ADVERSARY):
				troops_then = f2.troops+f2.prod*d
			self.send = troops_then+1
			# Compute the value of the move
			self.points = 0
			if (d == 0 or f1.owner != PLAYER or f1.troops < TROOP_MIN or self.send > f1.troops):
				return
			if (f2.owner == PLAYER):
				if (f2.troops < TROOP_MIN):
					self.points = 1
				return
			self.points = 1+f2.prod*f2.prod
			if (f1.troops > troops_then):
				self.points = self.points*10
			elif (f1.troops == troops_then and f1.prod > f2.prod):
				self.points = self.points*5
			self.points = self.points/math.sqrt(d)

		def getcmd(self):
			cmd = "MOVE "+str(self.src)+" "+str(self.dst)+" "+str(self.send)
			return cmd

		def debug(self):
			debug(str(self.src)+"->"+str(self.dst)+" : "+str(self.points))


# ------------------------------- Main program ---------------------------------
factory_count = int(input())  # the number of factories
map = Map(factory_count)

link_count = int(input())  # the number of links between factories
for i in range(link_count):
	f1, f2, d = [int(j) for j in input().split()]
	map.set_distance(f1, f2, d)
	map.set_distance(f2, f1, d) # Because is symetric

# game loop
while True:
	entity_count = int(input())  # the number of entities (e.g. factories and troops)
	debug("entity count "+str(entity_count))
	for i in range(entity_count):
		inputs = input().split()
		map.update_map(inputs)

	map.debug()
	map.act()

	#break # test local only
