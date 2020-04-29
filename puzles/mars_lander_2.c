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

typedef int error_t;

static void error_calculate(error_t *err, int obj, int pos, int spd)
{
	*err = obj + 10*spd - pos;
}

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
	int obj_x = (obj.x2 + obj.x1)/2;
	bool rigth;
	error_t err_x = 0, err_y = 0;
	int last_x = 0;
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

		if(X > obj.x2) {
			obj_x = obj.x2;
		} else if(X < obj.x1) {
			obj_x = obj.x1;
		} else {
			obj_x = X;
		}
		fprintf(stderr, "X[%d] obj_x[%d]\n", X, obj_x);

		error_calculate(&err_x, obj_x, X, -1*h_speed);
		fprintf(stderr, "err_x[%d] vx[%d], err_y[%d]\n", err_x, h_speed, err_y);
		int pwden = 4;
		int angle = 0;
		angle = -1*err_x/10;
		if(angle > 45)
			angle = 45;
		if(angle < -45)
			angle = -45;

		if(err_x > -10 && err_x < 10) {
			pwden = (v_speed<(-10))?4:2;
			pwden = (-1*v_speed)*4/10;
			if (pwden > 4)
				pwden = 4;
			if (pwden < 0)
				pwden = 0;
		}

		// rotate power. rotate is the desired rotation angle. power is the desired thrust power.
		printf("%d %d\n", angle, pwden);
	}

	return 0;
}
