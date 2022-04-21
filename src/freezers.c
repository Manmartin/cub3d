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

void	free_textures(t_scene_data *scene)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(scene->textures[i]);
		free(scene->cardinal[i]);
		i++;
	}
}

void	freezers(t_data *data)
{
	free_map(data->scene);
	free_textures(data->scene);
	free(data->scene);
}
