#include "cub3d.h"

void	print_map(t_scene_data *scene)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("%s\n", scene->textures[i]);
		i++;
	}
	i = 0;
	while (i < scene->height)
	{
		printf("%s\n", scene->map[i]);
		i++;
	}

}
