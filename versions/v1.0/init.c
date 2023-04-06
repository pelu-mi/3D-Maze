#include "maze.h"

/**
 * init - Initialize sdl and raycaster values
 * @sdl: SDL instance
 * @rc: Raycaster instance
 * Return: 0 if success, else -1
 */
int init(t_sdl *sdl, t_raycaster *rc)
{
	/* Initialize values in the structs */
	sdl->window = NULL;
	sdl->renderer = NULL;
	rc->player_pos_x = INIT_P_POS_X;
	rc->player_pos_y = INIT_P_POS_Y;
	rc->player_dir_x = INIT_P_DIR_X;
	rc->player_dir_y = INIT_P_DIR_Y;
	rc->player_plane_x = INIT_P_PLANE_X;
	rc->player_plane_y = INIT_P_PLANE_Y;
	/* Initialize SDL instance and handle errors */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "SDL Init Error: (%s)\n", SDL_GetError());
		return (-1);
	}
	if (SDL_CreateWindowAndRenderer(WIN_X, WIN_Y, 0,
				&sdl->window, &sdl->renderer) != 0)
	{
		fprintf(stderr, "SDL Create Error: (%s)\n", SDL_GetError());
		return (-1);
	}
	return (0);
}

/**
 * render_frame - Handle Rendering to window
 * @sdl: SDL instance
 * Return: Nothing
 */
void render_frame(t_sdl *sdl)
{
	SDL_RenderPresent(sdl->renderer);
	SDL_SetRenderDrawColor(sdl->renderer, 96, 128, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdl->renderer);
}
