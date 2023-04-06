#include "maze.h"

/**
 * convert_color - Convert hex to SDL_Color object
 * @hex: Hex value of color
 * Return: SDL Color object with RGB values
 */
SDL_Color convert_color(int hex)
{
	SDL_Color color;

	/* Convert hex to rgb values using shift operation */
	color.r = ((hex >> 16) & 0xFF);
	color.g = ((hex >> 8) & 0xFF);
	color.b = ((hex) & 0xFF);
	return (color);
}

/**
 * select_wall_color - Select wall color to be used based on map value
 * @map_x: x value on map
 * @map_y: y value on map
 * Return: SDL Color object with rgb values
 */
SDL_Color select_wall_color(int map_x, int map_y)
{
	SDL_Color color;

	if (worldMap[map_x][map_y] == 1)
		color = convert_color(RED);
	else if (worldMap[map_x][map_y] == 2)
		color = convert_color(GREEN);
	else if (worldMap[map_x][map_y] == 3)
		color = convert_color(BLUE);
	else if (worldMap[map_x][map_y] == 4)
		color = convert_color(WHITE);
	else if (worldMap[map_x][map_y] == 5)
		color = convert_color(SKY);
	else
		color = convert_color(BLACK);
	return (color);
}

/**
 * apply_night_effect - Apply night effect to color
 * @color: color value
 * @distance: Distance from player to color
 * Return: SDL Color object with rgb values
 */
SDL_Color apply_night_effect(SDL_Color color, double distance)
{
	if (color.r / distance * AMB_LIGHT <= color.r)
		color.r = color.r / distance * AMB_LIGHT;
	if (color.g / distance * AMB_LIGHT <= color.g)
		color.g = color.g / distance * AMB_LIGHT;
	if (color.b / distance * AMB_LIGHT <= color.b)
		color.b = color.b / distance * AMB_LIGHT;
	return (color);
}
