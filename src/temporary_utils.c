#include "cub3d.h"

void	print_map(t_scene_data *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->height)
	{
		printf("%s\n", scene->map[i]);
		i++;
	}

}
