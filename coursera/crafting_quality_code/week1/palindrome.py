import sys

def hello():
	print("Nuria Roca hija de puta")

def reverse(s):
	""" (str) -> str

	Retrurns a reversed version of s
	>>> reverse('hello')
	'olleh'
	"""
	rev = ''
	for ch in s:
		rev = ch + rev
	return rev

def is_palindrome_v1(s):
	""" (str) -> bool

	Return true if s is palindrome
	Reverses the whole string and compares
	"""
	return reverse(s) == s

def is_palindrome_v2(s):
	""" (str) -> bool

	Return true if s is palindrome
	Reverses half and compares
	"""
	n = len(s)
	# Compering the first half of s to the reverse of the second half
	# Omit the middle character of an odd-length string
	return s[:n // 2] == reverse(s[n - n//2:])

def is_palindrome_v3(s):
	""" (str) -> bool

	Return true if s is palindrome
	Compares pair of characters
	"""
	i = 0
	j = len(s) - 1
	while i < j and s[i] == s[j]:
		i = i + 1
		j = j - 1
	return i >= j

if __name__ == "__main__":
	args = sys.argv
	# args[0] = current file
	# args[1] = function name
	# args[2:] = function args : (*unpacked)
	globals()[args[1]](*args[2:])
