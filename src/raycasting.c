#include "maze.h"

/**
 * calcStepDist - Calculate step and distance from current pos to first X or Y
 * @rayPos: XY value of ray position
 * @rayDir: XY value of ray direction
 * @posToNext: Distance from position to next XY side
 * @distToNext: Distance from XY side to next XY side
 * @map: XY value of current position in maze
 * @step: XY direction to step in
 *
 * Return: Nothing
 */
void calcStepDist(point_t *rayPos, point_t *rayDir, point_t *posToNext,
		point_t *distToNext, SDL_Point *map, SDL_Point *step)
{
	if (rayDir->x < 0)
	{
		step->x = -1;
		posToNext->x = (rayPos->x - map->x) * distToNext->x;
	}
	else
	{
		step->x = 1;
		posToNext->x = (map->x + 1.0 - rayPos->x) * distToNext->x;
	}

	if (rayDir->y < 0)
	{
		step->y = -1;
		posToNext->y = (rayPos->y - map->y) * distToNext->y;
	}
	else
	{
		step->y = 1;
		posToNext->y = (map->y + 1.0 - rayPos->y) * distToNext->y;
	}
}


/**
 * findWall -  Move to next maze square in X or Y dir until wall is hit
 * @maze: 2D array of Maze layout
 * @posToNext:  Distance from position to next XY side
 * @distToNext: Distance from XY side to next XY side
 * @map: XY value of current position in maze
 * @step: XY direction to step in
 * @side: If wall hit is facing NS or EW
 *
 * Return: Nothing
 */
void findWall(int *maze, point_t *posToNext, point_t *distToNext,
		SDL_Point *map, SDL_Point *step, int *side)
{
	int hit = 0;

	while (hit == 0)
	{
		if (posToNext->x < posToNext->y)
		{
			posToNext->x += distToNext->x;
			map->x += step->x;
			*side = 0;
		}
		else
		{
			posToNext->y += distToNext->y;
			map->y += step->y;
			*side = 1;
		}

		/* check if ray hit a wall */
		if (*((int *)maze + map->x * MAP_WIDTH + map->y) > 0)
			hit = 1;
	}
}


/**
 * raycaster - Implement raycasting
 * @maze: 2D array of Maze layout
 * @textured: True if using textures, false if using colours
 *
 * Return: Nothing
 */
void raycaster(int *maze, bool textured)
{
	double cameraX;		/* X coordinate in camera space */
	point_t rayPos, rayDir;	/* XY value of ray pos & direction of ray */
	point_t posToNext, distToNext;/* Ray length: pos to XY pt & XY pt to XY pt */
	double distToWall;	/* Distance: player to wall */
	SDL_Point map, step;	/* XY value: current pos & direction to move (1/-1) */
	int side, x;		/* If wall hit is facing NS or EW & ray counter */

	/* cast ray x for every column w */
	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		/* calculate ray position and direction */
		cameraX = 2 * x / (double)(SCREEN_WIDTH) - 1;
		rayPos.x = pos.x;
		rayPos.y = pos.y;
		rayDir.x = dir.x + plane.x * cameraX;
		rayDir.y = dir.y + plane.y * cameraX;
		/* grid position on maze */
		map.x = (int)(rayPos.x);
		map.y = (int)(rayPos.y);
		/* measure distance to next X or Y intersection */
		distToNext.x = sqrt(1 + (pow(rayDir.y, 2)) / pow(rayDir.x, 2));
		distToNext.y = sqrt(1 + (pow(rayDir.x, 2)) / pow(rayDir.y, 2));

		/* calculate step and distance from pos to first X or Y*/
		calcStepDist(&rayPos, &rayDir, &posToNext, &distToNext, &map, &step);

		/* Move to next maze square in X or Y dir until wall is hit */
		findWall(maze, &posToNext, &distToNext, &map, &step, &side);

		/* calculate distance projected in camera direction */
		if (side == 0)
			distToWall = (map.x - rayPos.x + (1 - step.x) / 2) / rayDir.x;
		else
			distToWall = (map.y - rayPos.y + (1 - step.y) / 2) / rayDir.y;
		/* draw walls to buffer */
		renderWalls(maze, map, rayPos, rayDir, distToWall, x, side, textured);
	}
	/* draw updated buffer with walls, floor, and ceiling to renderer */
	updateRenderer(textured);
}
