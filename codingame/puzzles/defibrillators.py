import sys
import math

class Desfibrilator:
	def __init__(self):
		number = 0
		name = ''
		addr = ''
		phone = ''
		lon = 0
		lat = 0

	def print(self):
		print("number "+str(self.number)+" name ["+self.name+"] addr ["+ \
		self.addr+"] phone ["+self.phone+"] lat "+str(self.lat)+" lon "+ \
		str(self.lon), file=sys.stderr, flush=True)

	def parse(self, input):
		#1;Maison de la Prevention Sante;6 rue Maguelone 340000 Montpellier;;3,87952263361082;43,6071285339217
		#print("input: "+input, file=sys.stderr, flush=True)
		data = input.split(';')
		#print(data, file=sys.stderr, flush=True)
		self.number = int(data[0])
		self.name = data[1]
		self.addr = data[2]
		self.phone = data[3]
		self.lon = float(data[4].replace(',','.'))
		self.lat = float(data[5].replace(',','.'))
		#self.print()

	def copy(self, other):
		self.number = other.number
		self.name =  other.name
		self.addr =  other.addr
		self.phone =  other.phone
		self.lon = other.lon
		self.lat = other.lat


# Calculates the distance given two coordinates
def distance(lonA,lonB,latA,latB):
	x = (lonB-lonA)*math.cos((latA+latB)/2)
	y = (latB-latA)
	return (math.sqrt(x*x + y*y) * 6371)

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

lon = input().replace(',','.')
lat = input().replace(',','.')
print("coords "+lon+" "+lat, file=sys.stderr, flush=True)
n = int(input())
dwinner = Desfibrilator()
dobj = Desfibrilator()
d = float("inf")
for i in range(n):
	defib = input()
	dobj.parse(defib)
	dtmp = distance(float(lon), dobj.lon, float(lat), dobj.lat)
	if (dtmp < d) :
		print(str(dtmp)+" < "+str(d)+": "+str(i), file=sys.stderr, flush=True)
		d = dtmp
		dwinner.copy(dobj)

# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)

print(dwinner.name)
