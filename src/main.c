#include "maze.h"

/* Global variables */
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];
point_t pos;
point_t dir;
point_t plane;
double time;

/**
 * init_globals - Initialize global variables
 *
 * Return: Nothing
 */
void init_globals(void)
{
	pos.x = 1;
	pos.y = 12;
	dir.x = 1;
	dir.y = -0.66;
	plane.x = 0;
	plane.y = 0.66;
	time = 0;
}


/**
 * main - Put it all together
 * @argc: Number of args
 * @argv: Pointer to Array of args
 *
 * Return: 0 if success, else 1
 */
int main(int argc, char *argv[])
{
	int *maze = NULL; /* 2D array storing maze layout */
	char *mapName;
	bool textured;

	init_globals(); /* Initialize global variables */
	/* Handle command line arguments */
	mapName = "\0";
	textured = true; /* Set this to false to run the non-textured prototype */
	if (argc == 2)
		mapName = argv[1];
	else
		mapName = "maps/map_0";

	/* Initialize SDL */
	if (!initSDL())
		return (1);

	/* Parse maze map */
	maze = parseMap(mapName, maze);
	if (maze == NULL)
		return (1);
	if (textured)
		loadTextures(mapName);

	/* Run loop until user exits */
	while (!quit())
	{
		if (!textured)
			renderBGFlat();
		raycaster(maze, textured); /* Implement raycasting */
		input(maze); /* Handle user input */
	}

	closeSDL(maze); /* Cleanup */
	return (0);
}
