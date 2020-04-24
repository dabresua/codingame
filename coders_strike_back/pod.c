#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

#define DEBUG 1

#define KI 2
#define KD 2

static int calc_err_acu(int old_err, int nca, int spd, int ncd)
{
	int new_err = nca*spd/ncd;
	return new_err + old_err/KI + (new_err-old_err)/KD;
}

static inline int calc_vel(int x, int y, int lx, int ly)
{
	int dx = (x > lx)?(x - lx):(lx - x);
	int dy = (y > ly)?(y - ly):(ly - y);
	double ddx = (double)dx*(double)dx;
	double ddy = (double)dy*(double)dy;
	double r = sqrt(ddx+ddy);
	#ifdef DEBUG
	fprintf(stderr, "[%d, %d][%d, %d][%d, %d]\n", x, y, lx, ly, dx, dy);
	#endif /* DEBUG */
	return (int)r;
}

int main()
{

	// game loop
	int last_x = -1, last_y = -1;
	int err_acu = 0;
	while (1) {
		int x;
		int y;
		// x position of the next check point
		int next_checkpoint_x;
		// y position of the next check point
		int next_checkpoint_y;
		// distance to the next checkpoint
		int next_checkpoint_dist;
		// angle between your pod orientation and the direction of the next checkpoint
		int next_checkpoint_angle;
		scanf("%d%d%d%d%d%d", &x, &y, &next_checkpoint_x, &next_checkpoint_y,
		      &next_checkpoint_dist, &next_checkpoint_angle);
		#ifdef DEBUG
		fprintf(stderr, "[%d,%d][%d,%d][%d][%d]\n", x, y, next_checkpoint_x,
		        next_checkpoint_y, next_checkpoint_dist, next_checkpoint_angle);
		#endif /* DEBUG */
		int opponent_x;
		int opponent_y;
		scanf("%d%d", &opponent_x, &opponent_y);

		// Write an action using printf(). DON'T FORGET THE TRAILING \n
		// To debug: fprintf(stderr, "Debug messages...\n");
		int vel = 0;
		if(last_x != -1 && last_y != -1) {
			vel = calc_vel(x, y, last_x, last_y);
		}
		#ifdef DEBUG
		fprintf(stderr, "Vel %ld\n", vel);
		#endif /* DEBUG */
		last_x = x;
		last_y = y;

		// You have to output the target position
		// followed by the power (0 <= thrust <= 100)
		// i.e.: "x y thrust"
		int thrust = 100;
		if(next_checkpoint_angle < 0) {
			next_checkpoint_angle = -next_checkpoint_angle;
		}
		#if DEBUG
		fprintf(stderr, "Angle %d\n", next_checkpoint_angle);
		#endif /* DEBUG */

		if(next_checkpoint_angle > 90) {
			thrust = 0;
			printf("%d %d %d\n", next_checkpoint_x, next_checkpoint_y, thrust);
			err_acu = calc_err_acu(err_acu, next_checkpoint_angle, vel,
			                       next_checkpoint_dist);
			continue;
		}
		fprintf(stderr, "%d\n", next_checkpoint_angle*vel/next_checkpoint_dist);
		if(next_checkpoint_angle*vel > next_checkpoint_dist) {
			err_acu = calc_err_acu(err_acu, next_checkpoint_angle, vel,
			                       next_checkpoint_dist);
			thrust = 100 - err_acu;
			if(thrust < 0)
			    thrust = 0;
			printf("%d %d %d\n", next_checkpoint_x, next_checkpoint_y, thrust);
			continue;
		}
		err_acu = 0;
		if (next_checkpoint_angle == 0 && (next_checkpoint_dist > 8000 ||
		    next_checkpoint_dist > 5000 && vel < 300)) {
			printf("%d %d BOOST\n", next_checkpoint_x, next_checkpoint_y);
			continue;
		}

		if (next_checkpoint_dist < 3000 && next_checkpoint_dist > 0) {
		    int r = vel*100/next_checkpoint_dist;
		    if(r>60) {
		        r=60;
		    }
			thrust = 100 - vel*100/next_checkpoint_dist;
		}


		printf("%d %d %d\n", next_checkpoint_x, next_checkpoint_y, thrust);
	}

	return 0;
}
