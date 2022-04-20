#include "cub3d.h"

void	free_map(t_scene_data *scene)
{
	size_t	i;

	i = 0;
	while (scene->map && scene->map[i])
	{
		free(scene->map[i]);
		i++;
	}
	free(scene->map);
}

void	freezers(t_data *data)
{
	free_map(data->scene);
	free(data->scene);
}
