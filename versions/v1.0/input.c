#include "maze.h"

/**
 * turn - Handle turning the camera
 * @rc: Raycaster instance
 * @flag: Differentiate between left and right turns
 */
void turn(t_raycaster *rc, double flag)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = rc->player_dir_x;
	rc->player_dir_x = rc->player_dir_x * cos(ROT_SPEED * flag) -
		rc->player_dir_y * sin(ROT_SPEED * flag);
	rc->player_dir_y = oldDirX * sin(ROT_SPEED * flag) +
		rc->player_dir_y * cos(ROT_SPEED * flag);
	oldPlaneX = rc->player_plane_x;
	rc->player_plane_x = rc->player_plane_x * cos(ROT_SPEED * flag) -
		rc->player_plane_y * sin(ROT_SPEED * flag);
	rc->player_plane_y = oldPlaneX * sin(ROT_SPEED * flag) +
		rc->player_plane_y * cos(ROT_SPEED * flag);
}

/**
 * doKeyDown - Handle key presses
 * @rc: Raycaster instance
 * @key: SDL Keyboard Event Key
 */
void doKeyDown(t_raycaster *rc, SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_UP || key->keysym.sym == SDLK_w)
	{
		if (worldMap[(int)(rc->player_pos_x + rc->player_dir_x *
				MV_SPEED)][(int)(rc->player_pos_y)] == 0)
			rc->player_pos_x += rc->player_dir_x * MV_SPEED;
		if (worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y +
				rc->player_dir_y * MV_SPEED)] == 0)
			rc->player_pos_y += rc->player_dir_y * MV_SPEED;
	}
	if (key->keysym.sym == SDLK_DOWN || key->keysym.sym == SDLK_s)
	{
		if (worldMap[(int)(rc->player_pos_x - rc->player_dir_x *
				MV_SPEED)][(int)(rc->player_pos_y)] == 0)
			rc->player_pos_x -= rc->player_dir_x * MV_SPEED;
		if (worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y -
				rc->player_dir_y * MV_SPEED)] == 0)
			rc->player_pos_y -= rc->player_dir_y * MV_SPEED;
	}
	if (key->keysym.sym == SDLK_RIGHT || key->keysym.sym == SDLK_d)
	{
		turn(rc, -1.0);
	}
	if (key->keysym.sym == SDLK_LEFT || key->keysym.sym == SDLK_a)
	{
		turn(rc, 1.0);
	}
}


/**
 * handle_events - Handle key presses
 * @rc: Raycaster instance
 * Return: 0 to continue program and -1 to end it
 */
int handle_events(t_raycaster *rc)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		/* Handle keypresses */
		switch (event.type)
		{
			case SDL_QUIT:
				return (-1);
			case SDL_KEYDOWN:
				/* Handle the ESC key */
				if (event.key.keysym.scancode == 0x29)
					return (-1);
				doKeyDown(rc, &event.key);
				break;
			default:
				break;
		}
	}
	return (0);
}
