import sys
import math

# Grab the pellets as fast as you can!
def calc_value(x1, y1, x2, y2, val):
	dx = x1-x2
	dy = y1-y2
	dist = math.sqrt(dx**2 + dy**2)
	return val/dist

# width: size of the grid
# height: top left corner is (x=0, y=0)
width, height = [int(i) for i in input().split()]
for i in range(height):
	row = input()  # one line of the grid: space " " is floor, pound "#" is wall

# game loop
first = 1
while True:
	my_score, opponent_score = [int(i) for i in input().split()]
	visible_pac_count = int(input())  # all your pacs and enemy pacs in sight
	x_list = []
	y_list = []
	y_list = [] 
	pac_list = []
	speed_turns_left_list = []

	for i in range(visible_pac_count):
		# pac_id: pac number (unique within a team)
		# mine: true if this pac is yours
		# x: position in the grid
		# y: position in the grid
		# type_id: unused in wood leagues
		# speed_turns_left: unused in wood leagues
		# ability_cooldown: unused in wood leagues
		pac_id, mine, x, y, type_id, speed_turns_left, ability_cooldown = input().split()

		pac_id = int(pac_id)
		mine = mine != "0"
		if mine:
			x_list.append(int(x))
			y_list.append(int(y))
			pac_list.append(pac_id)
			speed_turns_left_list.append(int(speed_turns_left))

		ability_cooldown = int(ability_cooldown)

	visible_pellet_count = int(input())  # all pellets in sight


	best_list = [0]*len(x_list)
	x_obj = [0]*len(x_list)
	y_obj = [0]*len(x_list)
	command_list = ["MOVE"]*len(x_list)
	if first == 1:
		first = 0
		escape_obj = [-1]*len(x_list)
		x_last = [-1]*len(x_list)
		y_last = [-1]*len(x_list)
		cool_down = [0]*len(x_list)
		clockwise = [0]*len(x_list)

	for i in range(visible_pellet_count):
		# value: amount of points this pellet is worth
		x, y, value = [int(j) for j in input().split()]
		for j in range(len(x_list)):
			val = calc_value(x, y, x_list[j], y_list[j], value)
			b = best_list[j]
			if int(b) < val:
				best_list[j] = val
				x_obj[j] = x
				y_obj[j] = y

	for j in range(len(x_list)):
		print("now " + str(x_list[j]) + ", " + str(y_list[j]), file=sys.stderr)
		if best_list[j] == 0 or (x_last[j] == x_list[j] and y_last[j] == y_list[j]):
			escape = 1
			if escape_obj[j] == -1:
				recalculate = 1
			if x_last[j] == x_list[j] and y_last[j] == y_list[j]:
				if clockwise[j] == 1:
					clockwise[j] == 0
				else:
					clockwise[j] == 0
				recalculate = 1

			if recalculate == 1:
				if x_list[j] < width/2:
					escape_obj[j] = 0
				else:
					escape_obj[j] = 1
				if y_list[j] > height/2:
					escape_obj[j] = escape_obj[j]+2
			
			#Anti-clockwise
			if clockwise[j] == 1:
				if escape_obj[j] == 0:
					x_obj[j] = 0
					y_obj[j] = height-1
				elif escape_obj[j] == 1:
					x_obj[j] = 0
					y_obj[j] = 0
				elif escape_obj[j] == 2:
					x_obj[j] = width-1
					y_obj[j] = height-1
				elif escape_obj[j] == 3:
					x_obj[j] = width-1
					y_obj[j] = 0
			else :
				if escape_obj[j] == 0:
					x_obj[j] = 0
					y_obj[j] = height-1
				elif escape_obj[j] == 1:
					x_obj[j] = 0
					y_obj[j] = 0
				elif escape_obj[j] == 2:
					x_obj[j] = width-1
					y_obj[j] = height-1
				elif escape_obj[j] == 3:
					x_obj[j] = width-1
					y_obj[j] = 0
		print("speed " + str(speed_turns_left_list[j]), file=sys.stderr)
		if speed_turns_left_list[j] == 0 and cool_down[j] <= 0:
			command_list[j] = "SPEED"
			cool_down[j] = 10
		else:
			command_list[j] = "MOVE"
			cool_down[j] = cool_down[j] - 1

	# Write an action using print
	# To debug: print("Debug messages...", file=sys.stderr)

	# MOVE <pacId> <x> <y>
	str_out = ""
	for j in range(len(x_list)):
		x_last[j] = x_list[j]
		y_last[j] = y_list[j]
		str_out = str_out+ command_list[j] +" "+ str(pac_list[j]) + " " + str(x_obj[j]) + " " + str(y_obj[j])+"|"

	print(str_out)
