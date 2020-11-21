import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

class Symbol:
	def __init__(self, f, leaf, l, r):
		self.freq = f # Frequency of the symbol
		self.code = ""
		self.leaf = leaf
		if (self.leaf == False):
			self.freq = l.freq + r.freq
		self.l = l
		self.r = r

	def add_zero(self):
		if (self.leaf):
			self.append('0')
		else:
			self.l.add_zero()
			self.r.add_zero()

	def add_one(self):
		if (self.leaf):
			self.append('1')
		else:
			self.l.add_one()
			self.r.add_one()

	def append(self, char):
		self.code = self.code + char

	def get_weigth(self):
		return len(self.code)

	def get_cost(self):
		acu = self.get_weigth() * self.freq
		if (self.l is not None):
			acu = acu + self.l.get_cost()
		if (self.r is not None):
			acu = acu + self.r.get_cost()
		return acu

	def debug(self):
		if (self.leaf == True):
			print(str(self.freq)+":"+self.code, file=sys.stderr, flush=True)
		else:
			#print("father", file=sys.stderr, flush=True)
			self.l.debug()
			self.r.debug()

class SymbolTree:
	def __init__(self, freqs):
		print("freqs "+str(freqs), file=sys.stderr, flush=True)
		self.leafnodes = []
		# 1. Create leaf nodes
		for freq in freqs:
			sym = Symbol(freq, True, None, None)
			self.leafnodes.append(sym)

		if (len(self.leafnodes) == 1):
			s1 = self.leafnodes[0]
			s1.add_zero()

		while (len(self.leafnodes) > 1):
			# 2. Create empty node
			s1 = self.leafnodes[0]
			s2 = self.leafnodes[1]
			n = Symbol(0, False, s1, s2)
			s1.add_zero()
			s2.add_one()
			self.leafnodes[1]
			self.leafnodes = self.leafnodes[2:]
			self.leafnodes.append(n)
			self.leafnodes.sort(key=lambda x: x.freq)

	def debug(self):
		print("---- Tree ----", file=sys.stderr, flush=True)
		for sym in self.leafnodes:
			sym.debug()
		print("--------------", file=sys.stderr, flush=True)

	def result(self):
		acu = 0
		for sym in self.leafnodes:
			acu = acu + sym.get_cost()
		return acu

n = int(input())
wi=[]
print("n "+str(n), file=sys.stderr, flush=True)
for i in input().split():
	wi.append(int(i))
print("wi "+str(wi), file=sys.stderr, flush=True)
wi.sort()
print("wi "+str(wi), file=sys.stderr, flush=True)

alphabet = SymbolTree(wi)
alphabet.debug()

# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)

print(alphabet.result())
