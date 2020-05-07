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
while True:
    my_score, opponent_score = [int(i) for i in input().split()]
    visible_pac_count = int(input())  # all your pacs and enemy pacs in sight
    x_list = []
    y_list = []
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
        speed_turns_left = int(speed_turns_left)
        ability_cooldown = int(ability_cooldown)
    
    visible_pellet_count = int(input())  # all pellets in sight
    best_list = [0]*len(x_list)
    x_obj = [0]*len(x_list)
    y_obj = [0]*len(x_list)

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

    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)

    print("visible_pac_count " + str(visible_pac_count), file=sys.stderr)

    # MOVE <pacId> <x> <y>
    for j in range(len(x_list)):
         print("MOVE "+ str(j) + " " + str(x_obj[j]) + " " + str(y_obj[j]))
