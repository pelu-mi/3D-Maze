#include "maze.h"

/**
 * initial_calc - Handle the initialization of valies in every frame
 * @rc: Raycaster instance
 * @x: ray to be traced
 */
void initial_calc(t_raycaster *rc, int x)
{
	double camera_x;

	/* Find new x and y values for ray */
	camera_x = 2 * x / (double)(WIN_X) - 1;
	rc->ray_dir_x = rc->player_dir_x + rc->player_plane_x * camera_x;
	rc->ray_dir_y = rc->player_dir_y + rc->player_plane_y * camera_x;
	/* Set map coordinates to player coordinates */
	rc->map_x = (int)(rc->player_pos_x);
	rc->map_y = (int)(rc->player_pos_y);
	/* Set delta values based on formula */
	rc->delta_dist_x = sqrt(1 + pow(rc->ray_dir_y, 2) / pow(rc->ray_dir_x, 2));
	rc->delta_dist_y = sqrt(1 + pow(rc->ray_dir_x, 2) / pow(rc->ray_dir_y, 2));
	/* Set Step and side values based on if ray_dir is < or > 0 */
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->player_pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->player_pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->player_pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->player_pos_y) * rc->delta_dist_y;
	}
}

/**
 * perform_dda - Handle Digital Difference Analysis
 * @rc: Raycaster instance
 */
void perform_dda(t_raycaster *rc)
{
	int hit = 0;

	while (hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (worldMap[rc->map_x][rc->map_y] > 0)
			hit = 1;
	}
}


/**
 * calc_wall_height - Calculate wall height for each ray
 * @rc: Raycaster instance
 */
void calc_wall_height(t_raycaster *rc)
{
	int line_height;

	/* Set perpendicular wall distance based on value of side */
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - rc->player_pos_x +
				(1 - rc->step_x) / 2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - rc->player_pos_y +
				(1 - rc->step_y) / 2) / rc->ray_dir_y;
	/* Set value of line_height */
	line_height = (int)(WIN_Y / rc->perp_wall_dist);
	/* Calculate starting point and end point for drawing wall on ray */
	rc->draw_start = -line_height / 2 + WIN_Y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = line_height / 2 + WIN_Y / 2;
	if (rc->draw_end >= WIN_Y)
		rc->draw_end = WIN_Y - 1;
}


/**
 * draw_vert_line - Draw vertical line for each ray in the frame
 * @sdl: SDL instance
 * @rc: Raycaster instance
 * @x: Ray X to be cast to the screen
 */
void draw_vert_line(t_sdl *sdl, t_raycaster *rc, int x)
{
	SDL_Color color;

	/* Set the color to be drawn based on the distance and value in map */
	color = apply_night_effect(select_wall_color(rc->map_x, rc->map_y),
			rc->perp_wall_dist);
	/* Change color based on the if the wall is vertical or horizontal */
	if (rc->side == 1)
	{
		color.r /= 2;
		color.g /= 2;
		color.b /= 2;
	}
	/* Draw the line using the renderer */
	SDL_SetRenderDrawColor(sdl->renderer, color.r, color.g, color.b,
			SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(sdl->renderer, x, rc->draw_start, x, rc->draw_end);
}
