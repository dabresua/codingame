import sys
import math
import re

class Mime:
	def __init__(self):
		self.ext = ""
		self.mt = ""

	def __init__(self,e,m):
		self.ext = e.lower()
		self.mt = m

	def debug(self):
		print("ext ["+self.ext+"] mt["+self.mt+"]", file=sys.stderr, flush=True)

class MimeList:
	def __init__(self):
		self.array = []

	def insert(self, m):
		self.array.append(m)

	def search(self, ex):
		for mime in self.array:
			if (ex.lower() == mime.ext):
				return mime.mt
		return "UNKNOWN"

	def debug(self):
		print("----------------------------------", file=sys.stderr, flush=True)
		for mime in self.array:
			mime.debug()
		print("----------------------------------", file=sys.stderr, flush=True)

class MimeBSTnode:
	def __init__(self, m):
		self.mime = m
		self.right = None
		self.left = None

	def insert(self, m):
		if (self.mime):
			if (m.ext < self.mime.ext):
				if (self.left is None):
					self.left = MimeBSTnode(m)
				else:
					self.left.insert(m)
			elif (m.ext > self.mime.ext):
				if (self.right is None):
					self.right = MimeBSTnode(m)
				else:
					self.right.insert(m)
		else:
			self.mime = m

	def search(self, ex):
		if (ex < self.mime.ext):
			if (self.left is None):
				return "UNKNOWN"
			else:
				return self.left.search(ex)
		elif (ex > self.mime.ext):
			if (self.right is None):
				return "UNKNOWN"
			else:
				return self.right.search(ex)
		else:
			return self.mime.mt

	def debug(self):
		if (self.left):
			self.left.debug()
		self.mime.debug()
		if (self.right):
			self.right.debug()

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())  # Number of elements which make up the association table.
q = int(input())  # Number Q of file names to be analyzed.
array = MimeList()
root = MimeBSTnode(None)
for i in range(n):
	# ext: file extension
	# mt: MIME type.
	ext, mt = input().split()
	tmp_mime = Mime(ext, mt)
	array.insert(tmp_mime)
	root.insert(tmp_mime)
	print("ext ["+ext+"] mt["+mt+"]", file=sys.stderr, flush=True)

array.debug()
print("------------------------------------------", file=sys.stderr, flush=True)
root.debug()
print("------------------------------------------", file=sys.stderr, flush=True)

for i in range(q):
	fname = input()  # One file name per line.
	print("fname["+fname+"]", file=sys.stderr, flush=True)
	try:
		name, ext = fname.rsplit('.',1)
		#print(array.search(ext))
		print(root.search(ext.lower()))
	except:
		print("UNKNOWN")

# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)


# For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
#print("UNKNOWN")
