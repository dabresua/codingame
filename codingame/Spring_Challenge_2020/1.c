#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Grab the pellets as fast as you can!
 **/

int main()
{
	// size of the grid
	int width;
	// top left corner is (x=0, y=0)
	int height;
	scanf("%d%d", &width, &height); fgetc(stdin);
	for (int i = 0; i < height; i++) {
		// one line of the grid: space " " is floor, pound "#" is wall
		char row[width + 1];
		fgets(row, width + 1, stdin);
	}

	// game loop
	while (1) {
		int my_score;
		int opponent_score;
		scanf("%d%d", &my_score, &opponent_score);
		// all your pacs and enemy pacs in sight
		int visible_pac_count;
		scanf("%d", &visible_pac_count);
		fprintf(stderr, "visible_pac_count %d\n", visible_pac_count);
		for (int i = 0; i < visible_pac_count; i++) {
			// pac number (unique within a team)
			int pac_id;
			// true if this pac is yours
			bool mine;
			// position in the grid
			int x;
			// position in the grid
			int y;
			// unused in wood leagues
			char type_id[10];
			// unused in wood leagues
			int speed_turns_left;
			// unused in wood leagues
			int ability_cooldown;
			int _mine;
			scanf("%d%d%d%d%s%d%d", &pac_id, &_mine, &x, &y, type_id, &speed_turns_left, &ability_cooldown);
			fprintf(stderr, "[%d][%d][%d][%d]%s[%d][%d]", &pac_id, &_mine, &x, &y, type_id, &speed_turns_left, &ability_cooldown);
			mine = _mine;
		}
		// all pellets in sight
		int visible_pellet_count;
		scanf("%d", &visible_pellet_count);
		fprintf(stderr, "visible_pellet_count %d\n", visible_pellet_count);
		for (int i = 0; i < visible_pellet_count; i++) {
			int x;
			int y;
			// amount of points this pellet is worth
			int value;
			scanf("%d%d%d", &x, &y, &value);
			fprintf(stderr, "x %d, y %d, value %d\n", x, y, value);
		}

		// Write an action using printf(). DON'T FORGET THE TRAILING \n
		// To debug: fprintf(stderr, "Debug messages...\n");

		printf("MOVE 0 15 10\n"); // MOVE <pacId> <x> <y>
	}

	return 0;
}
