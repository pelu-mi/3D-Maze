#include "maze.h"

/**
 * initSDL - Initialize SDL, window and renderer instances
 *
 * Return: true if successful, else false
 */
bool initSDL(void)
{
	/* Initialize window and renderer instances */
	window = NULL;
	renderer = NULL;

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (false);
	}

	/* Create new window, renderer and texture instances */
	window = SDL_CreateWindow("---Maze---", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (false);
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (texture == NULL)
	{
		fprintf(stderr, "SDL_CreateTexture Error: %s\n", SDL_GetError());
		return (false);
	}

	/* If all goes well, continue execution */
	return (true);
}

/**
 * closeSDL - Destroy instances created by initSDL and free memory
 * @maze: 2D array storing maze layout
 *
 * Return: Nothing
 */
void closeSDL(int *maze)
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	free(maze);
}
