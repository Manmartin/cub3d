#include "cub3d.h"

int check_valid_map(size_t x, size_t y, char **map, t_scene_data *scene)
{
//	printf("checking pos %zu, %zu\n", x, y);
	if ((x == scene->width - 1 || x == 0) && map[y][x] == ' ')
	{
		scene->valid_map = 0;
		return (-1);
	}
	if ((y == scene->height - 1 || y == 0) && map[y][x] == ' ')
	{
		scene->valid_map = 0;
		return (-1);
	}
	if (map[y][x] == 'N' || map[y][x] == '0')
		map[y][x] = 'x';
	else if (map[y][x] == '1')
		return (0);
	else
	{
//		scene->valid_map = 0;
		return (-1);
	}
	check_valid_map(x, y + 1, map, scene);
	check_valid_map(x + 1, y, map, scene);
	check_valid_map(x, y - 1, map, scene);
	check_valid_map(x - 1, y, map, scene);
	if (scene->valid_map == 0)
		return (-1);
	return (0);
}
