#include "maze.h"

/**
 * turn - Implement turning
 * @rotSpeed: Rotation speed
 * @flag: -1.0 to turn right and +1.0 to turn left
 *
 * Return: Nothing
 */
void turn(double rotSpeed, double flag)
{
	double oldDirX, oldPlaneX; /* Previous values of dir.x and plane.x */

	/* Rotate camera direction */
	oldDirX = dir.x;
	dir.x = dir.x * cos(rotSpeed * flag) - dir.y * sin(rotSpeed * flag);
	dir.y = oldDirX * sin(rotSpeed * flag) + dir.y * cos(rotSpeed * flag);

	/* Rotate camera plane */
	oldPlaneX = plane.x;
	plane.x = plane.x * cos(rotSpeed * flag) - plane.y * sin(rotSpeed * flag);
	plane.y = oldPlaneX * sin(rotSpeed * flag) + plane.y * cos(rotSpeed * flag);
}


/**
 * move - Implement movement based on direction
 * @maze: Current state of maze
 * @moveSpeed: Movement speed
 * @flag: 1 - forward, 2 - backward, 3 - left, 4 - right
 *
 * Return: Nothing
 */
void move(int *maze, double moveSpeed, int flag)
{
	/* Move forward */
	if (flag == 1)
	{
		if (!*((int *)maze + (int)(pos.x + dir.x * moveSpeed)
				* MAP_WIDTH + (int)pos.y))
			pos.x += dir.x * moveSpeed;
		if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
				(int)(pos.y + dir.y * moveSpeed)))
			pos.y += dir.y * moveSpeed;
	}
	/* Move backward */
	else if (flag == 2)
	{
		if (!*((int *)maze + (int)(pos.x - dir.x * moveSpeed)
				* MAP_WIDTH + (int)pos.y))
			pos.x -= dir.x * moveSpeed;
		if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
				(int)(pos.y - dir.y * moveSpeed)))
			pos.y -= dir.y * moveSpeed;
	}
	/* Strafe left */
	else if (flag == 3)
	{
		if (!*((int *)maze + (int)(pos.x - plane.x * moveSpeed)
					* MAP_WIDTH + (int)pos.y))
			pos.x -= plane.x * moveSpeed;
		if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
			(int)(pos.y - plane.y * moveSpeed)))
			pos.y -= plane.y * moveSpeed;
	}
	/* Strafe right */
	else if (flag == 4)
	{
		if (!*((int *)maze + (int)(pos.x + plane.x * moveSpeed)
					* MAP_WIDTH + (int)pos.y))
			pos.x += plane.x * moveSpeed;
		if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
			(int)(pos.y + plane.y * moveSpeed)))
			pos.y += plane.y * moveSpeed;
	}
}

/**
 * input - Handle user input
 * @maze: Current state of maze
 *
 * Return: Nothing
 */
void input(int *maze)
{
	const uint8_t *keystate;	/* Current key state */
	double oldTime;			/* Time taken to load the  previous frame */
	double frameTime;		/* Time taken to load the frame in seconds */
	double moveSpeed;		/* Move speed */
	double rotSpeed;		/* Rotation speed */
	int x_mouse;			/* Track mouse movement */

	/* Initialize values */
	keystate = SDL_GetKeyboardState(NULL);
	SDL_GetRelativeMouseState(&x_mouse, NULL);
	oldTime = time;
	time = SDL_GetTicks();
	frameTime = (time - oldTime) / 1000.0;
	moveSpeed = frameTime * 5.0;
	rotSpeed = frameTime * 3.0;

	/* Turn left + mouse handling */
	if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT] || x_mouse > 0)
		turn(rotSpeed, 1.0);

	/* Turn Right + mouse handling */
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT] || x_mouse < 0)
		turn(rotSpeed, -1.0);

	/* Move forward + collision handling */
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP])
		move(maze, moveSpeed, 1);

	/* Move backward + collision handling */
	if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN])
		move(maze, moveSpeed, 2);

	/* Strafe left */
	if (keystate[SDL_SCANCODE_Q])
		move(maze, moveSpeed, 3);

	/* Strafe right */
	if (keystate[SDL_SCANCODE_E])
		move(maze, moveSpeed, 4);
}

/**
 * quit - Check if user tries to quit
 * Return: True if user tries to quit, else false
 */
bool quit(void)
{
	SDL_Event event;	/* SDL Event listener instance */
	uint32_t windowFlags;	/* Flags for Window */

	/* Check all events in the events listener queue */
	while (SDL_PollEvent(&event) != 0)
	{
		/* If window's close button or ESC is pressed, exit */
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
					event.key.keysym.sym == SDLK_ESCAPE))
			return (true);

		/* Toggle between windowed and fullscreen modes */
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
		{
			windowFlags = SDL_GetWindowFlags(window);
			if (windowFlags & SDL_WINDOW_FULLSCREEN)
				SDL_SetWindowFullscreen(window, SDL_FALSE);
			else
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		}
	}

	/* Continue execution */
	return (false);
}
