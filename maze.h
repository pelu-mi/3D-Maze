#ifndef MAZE_H_
#define MAZE_H_

/* Include statements */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

/* Constants */
#define mapWidth	24
#define mapHeight	24
#define WIN_X		1280
#define WIN_Y           720
#define INIT_P_POS_X    22
#define INIT_P_POS_Y    12
#define INIT_P_DIR_X    -1
#define INIT_P_DIR_Y    0
#define INIT_P_PLANE_X  0
#define INIT_P_PLANE_Y  0.66
#define MV_SPEED        0.199
#define ROT_SPEED       0.1745
#define AMB_LIGHT       7

/* World Map in Maze */
extern int worldMap[mapWidth][mapHeight];


/* Colours */
#define WHITE           0xFFFFFF
#define RED             0xFF0000
#define GREEN           0x00FF00
#define BLUE            0x0000FF
#define BLACK           0x000000
#define SKY             0x87CEEB
#define FLOOR           0x7CFC00


/* ------------------------------------ */
/* Structs                              */
/* ------------------------------------ */

/**
 * struct s_sdl - Struct containing renderer and window
 * @window: SDL Window instance
 * @renderer: SDL Renderer instance
 *
 * Description: SDL instance to use throughout the program
 */
typedef struct s_sdl
{
	SDL_Window	*window;
	SDL_Renderer	*renderer;
} t_sdl;

/**
 * struct s_raycaster - Raycaster object for all variables to be used
 * @player_pos_x: all variables relating to player
 * @player_pos_y: all variables relating to player
 * @player_dir_x: all variables relating to player
 * @player_dir_y: all variables relating to player
 * @player_plane_x: all variables relating to player
 * @player_plane_y: all variables relating to player
 * @ray_dir_x: all variables relating to the ray
 * @ray_dir_y: all variables relating to the ray
 * @map_x: all variables relating to the map
 * @map_y: all variables relating to the map
 * @side_dist_x: Variables relating to the side
 * @side_dist_y: Variables relating to the side
 * @side: Variables relating to the side
 * @delta_dist_x: Variables relating to change in x
 * @delta_dist_y: Variables relating to change in y
 * @step_x: variables relating to step
 * @step_y: variables relating to step
 * @draw_start: variables relating to draw
 * @draw_end: variables relating to draw
 * @perp_wall_dist: varaible representing perpendicular dist
 *
 * Description: All variables required for raycasting will be stored here
 */
typedef struct s_raycaster
{
	double          player_pos_x;
	double          player_pos_y;
	double          player_dir_x;
	double          player_dir_y;
	double          player_plane_x;
	double          player_plane_y;
	double          ray_dir_x;
	double          ray_dir_y;
	int             map_x;
	int             map_y;
	double          side_dist_x;
	double          side_dist_y;
	double          delta_dist_x;
	double          delta_dist_y;
	int             step_x;
	int             step_y;
	int             side;
	int             draw_start;
	int             draw_end;
	double          perp_wall_dist;
} t_raycaster;


/* ------------------------------------ */
/* Function Prototypes                  */
/* ------------------------------------ */

/* color.c */
SDL_Color convert_color(int hexa_value);
SDL_Color select_wall_color(int map_x, int map_y);
SDL_Color apply_night_effect(SDL_Color color, double distance);

/* init.c */
int init(t_sdl *sdl, t_raycaster *rc);
void render_frame(t_sdl *sdl);

/* raycasting.c */
void initial_calc(t_raycaster *rc, int x);
void perform_dda(t_raycaster *rc);
void calc_wall_height(t_raycaster *rc);
void draw_vert_line(t_sdl *sdl, t_raycaster *rc, int x);

/* input.c */
void turn(t_raycaster *rc, double flag);
void doKeyDown(t_raycaster *rc, SDL_KeyboardEvent *event);
int handle_events(t_raycaster *rc);

/* main.c */
void raycaster(t_sdl *sdl, t_raycaster *rc);


#endif
