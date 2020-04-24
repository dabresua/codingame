#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef struct objective_t {
	int x1;
	int x2;
	int y;
	bool ok;
} objective_t;

#define OBJECTIVE_FMT "%s x:[%d %d] y: %d"
#define OBJECTIVE_PRM(_obj) (_obj).ok?"OK":"ERR", (_obj).x1, (_obj).x2, (_obj).y

int main()
{
	// the number of points used to draw the surface of Mars.
	int surface_n;
	objective_t obj = {.x1=0, .x2=0, .y=0, .ok = false};
	scanf("%d", &surface_n);
	for (int i = 0; i < surface_n; i++) {
		// X coordinate of a surface point. (0 to 6999)
		int land_x;
		// Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
		int land_y;
		scanf("%d%d", &land_x, &land_y);
		if(i == 0) {
			obj.x1 = land_x;
			obj.y = land_y;
			continue;
		}
		if(!obj.ok) {
			if(land_y == obj.y) {
				obj.x2 = land_x;
				obj.ok = (obj.x2 - obj.x1 >= 1000);
			} else {
				obj.x1 = land_x;
				obj.y = land_y;
			}
		} else {
			if(land_y == obj.y) {
				obj.x2 = land_x;
			}
		}
	}

	fprintf(stderr, OBJECTIVE_FMT "\n", OBJECTIVE_PRM(obj));

	// game loop
	while (1) {
		int X;
		int Y;
		// the horizontal speed (in m/s), can be negative.
		int h_speed;
		// the vertical speed (in m/s), can be negative.
		int v_speed;
		// the quantity of remaining fuel in liters.
		int fuel;
		// the rotation angle in degrees (-90 to 90).
		int rotate;
		// the thrust power (0 to 4).
		int power;
		scanf("%d%d%d%d%d%d%d", &X, &Y, &h_speed, &v_speed, &fuel, &rotate, &power);

		// Write an action using printf(). DON'T FORGET THE TRAILING \n
		// To debug: fprintf(stderr, "Debug messages...\n");


		// rotate power. rotate is the desired rotation angle. power is the desired thrust power.
		printf("-20 3\n");
	}

	return 0;
}
