#include "maze.h"

/**
 * loadToSurface - load textures from image to SDL Surface
 * @texSrc: Array to store loaded textures
 * @flag: 1 for default and 2 for other format
 *
 * Return: Nothing
 */
void loadToSurface(SDL_Surface **texSrc, int flag)
{
	/* Load three types of surfaces */
	if (flag == 1)
	{
		texSrc[0] = IMG_Load("textures/wall1.png");
		texSrc[1] = IMG_Load("textures/wall2.png");
		texSrc[2] = IMG_Load("textures/windowtree.png");
		texSrc[3] = IMG_Load("textures/windowspooky.png");
		texSrc[4] = IMG_Load("textures/ceiling.png");
		texSrc[5] = IMG_Load("textures/floorboards.png");
	}
	else if (flag == 2)
	{
		texSrc[0] = IMG_Load("textures/graystone.png");
		texSrc[1] = IMG_Load("textures/mossystone.png");
		texSrc[2] = IMG_Load("textures/door.png");
		texSrc[3] = IMG_Load("textures/guard.png");
		texSrc[4] = IMG_Load("textures/sky.png");
		texSrc[5] = IMG_Load("textures/grass.png");
	}
	else
	{
		texSrc[0] = IMG_Load("textures/hedge1.png");
		texSrc[1] = IMG_Load("textures/hedge2.png");
		texSrc[2] = IMG_Load("textures/gate.png");
		texSrc[3] = IMG_Load("textures/guard.png");
		texSrc[4] = IMG_Load("textures/sky.png");
		texSrc[5] = IMG_Load("textures/grass.png");
	}
}


/**
 * loadTextures - Load texture from file & store pixel data in 'tiles' buffer
 * @mapFile: Path to map loaded
 *
 * Return: Nothing
 */
void loadTextures(char *mapFile)
{
	SDL_Surface *texSrc[TEX_COUNT];/* Array to store textures */
	uint8_t *pixel;			/* Pixel color value at specific coordinate */
	int i, j, k;			/* Loop counters */

	/* Load textures for alx clone */
	if (strcmp(mapFile, "maps/map_clone") == 0)
		loadToSurface(texSrc, 1);

	/* Load textures for other maps */
	else if (strcmp(mapFile, "maps/map_0") == 0)
		loadToSurface(texSrc, 2);
	else
		loadToSurface(texSrc, 3);

	/* Get colours from texture pixels and store in 'tiles' array */
	for (i = 0; i < TEX_COUNT; i++)
	{
		for (j = 0; j < TEX_HEIGHT; j++)
		{
			for (k = 0; k < TEX_WIDTH; k++)
			{
				pixel = (uint8_t *)texSrc[i]->pixels + k * texSrc[i]->pitch + j *
					texSrc[i]->format->BytesPerPixel;

				tiles[i][j][k] = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
			}
		}
	}

	/* Free SDL_Surfaces memory */
	for (i = 0; i < TEX_COUNT; i++)
	{
		SDL_FreeSurface(texSrc[i]);
		texSrc[i] = NULL;
	}
}
