#include "maze.h"

/**
 * parseMap - Parse map from file to create maze layout
 * @filename: path to map file
 * @map: Array to store map
 *
 * Return: Array stored in map
 */
int *parseMap(char *filename, int *map)
{
	FILE *fp;
	char row[MAP_WIDTH * 2]; /* multiply by 2 because of spaces in map file */
	char *num;
	int i, j;

	/* Initialize file pointer */
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("File could not be opened");
		return (NULL);
	}

	/* Assign memory to map */
	map = malloc(sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
	if (map == NULL)
		return (NULL);

	/* Parse file and store in map */
	i = 0;
	while (fgets(row, sizeof(row), fp) != NULL)
	{
		/* if row contains only '\n', go to next row */
		if (strlen(row) <= 1)
			continue;

		num = strtok(row, "\n ");

		j = 0;
		while (num != NULL)
		{
			map[i * MAP_WIDTH + j] = atoi(num);
			num = strtok(NULL, "\n ");
			j++;
		}
		i++;
	}
	/* Close file pointer */
	fclose(fp);
	return (map);
}
