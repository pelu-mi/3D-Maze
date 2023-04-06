#ifndef MAZE_H_
#define MAZE_H_

/* ------------------------------------ */
/* Header files                         */
/* ------------------------------------ */

/* SDL2 libraries */
#include <SDL2/SDL.h>
#include <SDL_image.h>

/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>



/* ------------------------------------ */
/* Macros                               */
/* ------------------------------------ */

/* Screen Dimensions */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

/* Texture dimensions */
#define TEX_COUNT 6
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

/* Map Dimensions */
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define MAP_CHAR_COUNT 1275



/* ------------------------------------ */
/* Structs                              */
/* ------------------------------------ */

/**
 * struct point_s - Datatype for X-Y coordinate system
 * @x: X coordinate
 * @y: Y coordinate
 *
 * Description: This will store X and Y values for coordinate systems
 */
typedef struct point_s
{
	double x;
	double y;
} point_t;



/* ------------------------------------ */
/* Global variables                     */
/* ------------------------------------ */

/* SDL Window instance */
extern SDL_Window *window;

/* SDL Renderer instance */
extern SDL_Renderer *renderer;

/* SDL Texture instance */
extern SDL_Texture *texture;

/* Buffer to use for textures */
extern uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

/* Array to store textures */
extern uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];

/* Player position coordinates */
extern point_t pos;

/* Player direction vector */
extern point_t dir;

/* Camera plane */
extern point_t plane;

/* Time of current frame in view */
extern double time;



/* ------------------------------------ */
/* Files and Function prototypes        */
/* ------------------------------------ */

/* init.c */
bool initSDL(void);
void closeSDL(int *maze);

/* parse_map.c */
int *parseMap(char *filename, int *map);

/* input.c */
void turn(double rotSpeed, double flag);
void move(int *maze, double moveSpeed, int flag);
void input(int *maze);
bool quit(void);

/* texturing.c */
void loadToSurface(SDL_Surface **texSrc, int flag);
void loadTextures(char *mapName);

/* raycasting.c*/
void calcStepDist(point_t *rayPos, point_t *rayDir, point_t *posToNext,
		point_t *distToNext, SDL_Point *map, SDL_Point *step);
void findWall(int *maze, point_t *posToNext, point_t *distToNext, SDL_Point *map,
		SDL_Point *step, int *side);
void raycaster(int *maze, bool textured);

/* renderer.c*/
void updateRenderer(bool textured);
void renderWalls(int *maze, SDL_Point map, point_t rayPos, point_t rayDir,
		double distToWall, int x, int side, bool textured);
void renderBGFlat(void);
void renderWalls(int *maze, SDL_Point map, point_t rayPos, point_t rayDir,
		double distToWall, int x, int side, bool textured);
void renderBGTex(SDL_Point map, point_t rayDir, double distToWall,
		double wallX, int drawEnd, int x, int side);

/* main.c */
void init_globals(void);

#endif /* MAZE_H_ */
