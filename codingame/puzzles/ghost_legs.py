import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

class Runner:
	def __init__(self, name, p):
		self.name = name
		self.p = p

	def swap(self, line, max):
		#print("line "+line+" max "+str(max)+" p"+str(self.p), file=sys.stderr, flush=True)
		if (self.p > 1):
			#print("p > 1:"+line[self.p-2], file=sys.stderr, flush=True)
			if (line[self.p-2] == '-'):
				#print("Case 1", file=sys.stderr, flush=True)
				self.p = self.p-3
				return

		if (self.p < max):
			#print("p < max:"+line[self.p], file=sys.stderr, flush=True)
			if (line[self.p] == '-'):
				#print("Case 2", file=sys.stderr, flush=True)
				self.p = self.p+3
				return

		#print("Case 3", file=sys.stderr, flush=True)

w, h = [int(i) for i in input().split()]
print("w " + str(w) + " h " + str(h), file=sys.stderr, flush=True)

runners = []
results = []
for i in range(h):
	line = input()
	print("line "+line, file=sys.stderr, flush=True)
	if (i == 0):
		for j in range(w):
			if (line[j] != ' '):
				#print(str(j)+" is "+line[j], file=sys.stderr, flush=True)
				runners.append(Runner(line[j], j+1))
				results.append(" ")
	else:
		for j in range(len(runners)):
			runners[j].swap(line, w)
			results[j] = line[runners[j].p-1]

# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)

for j in range(len(runners)):
	print(runners[j].name+results[j])
