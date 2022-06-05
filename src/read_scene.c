#include "cub3d.h"

int	read_scene(t_data *data,t_scene_data *scene)
{
	if (copy_map(scene))
		return (1);
	if (check_input_schema(scene)) 
	{
		free_basics(data, scene);
		ft_putstr_fd("Wrong map\n", 2);
		return (1);
	}
	if (get_scene_size(scene, &scene->width, &scene->height))
	{
		free_basics(data, scene);
		ft_putstr_fd("Wrong map\n", 2);
		return (1);
	}
	if (parse_scene(data, scene))
	{
		return (1);
	}
//	print_map(scene);
//	printf("width %li, height %li", scene->width, scene->height);
	return (0);
}

int		parse_texture_paths(t_scene_data *scene, t_line *l)
{
	size_t	i;
	char	*aux;

	scene->cardinal[0] = ft_strdup("NO ");
	scene->cardinal[1] = ft_strdup("SO ");
	scene->cardinal[2] = ft_strdup("WE ");
	scene->cardinal[3] = ft_strdup("EA ");
	i = 0;
	while (i < 4)
	{
		aux = l->line;
		if (ft_strncmp(aux, scene->cardinal[i], 3) == 0)
		{
			aux += 3;
			scene->textures[i] = ft_substr(aux, 0, ft_strchr(aux, '\n') - aux);
		}
		else
			return (free_cardinals(scene));
		l = l->next;
		i++;
	}
	l = l->next;
	free_cardinals(scene);
	return (0);
}

int		parse_scene(t_data *data, t_scene_data *scene)
{
	int	i;
	int	j;
	t_line	*l;

	i = 0;
	j = 0;
	l = scene->map_start;
	if (parse_texture_paths(scene, *(scene->scene_list)) == 1)
	{
		free_basics(data, scene);
		ft_putstr_fd("Error parsing texture paths\n", 2);
		return (1);
	}
	if (check_texture_names(scene) || parse_colors(scene, scene->colors_start))
	{
		free_basics(data, scene);
		return (1);
	}
	scene->map = malloc(sizeof(char *) * (scene->height + 1));
	while (l)
	{
		scene->map[i] = malloc(sizeof(char) * scene->width + 1);
		while (j < (int) ft_strlen(l->line) - 1)
		{
			scene->map[i][j] = l->line[j];
			if (ft_strchr("NSEW", l->line[j]))
			{
				if (data->game->found_player == 0)
					data->game->found_player = 1;
				else
				{
				//	free_map(data->scene);
					free_map_partially(scene, i + 1);
					free_basics(data, scene);
					//freezers?
					ft_putstr_fd("Error: 2 players found\n", 2);	
					return (1);
				}
				data->game->player->x = j;
				data->game->player->y = i;
			//	printf("[%f %f]\n", data->game->player->x, data->game->player->y);
			}
			else if (ft_strchr(" 10", l->line[j]) == 0)
			{
				//freezers?
				ft_putstr_fd("Error: unexpected character\n", 2);
				ft_putchar_fd(l->line[j], 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
			j++;
		}
		while (j < scene->width)
		{
			scene->map[i][j] = ' ';
			j++;
		}
		scene->map[i][j] = 0;
		j = 0;
		l = l->next;
		i++;
	}
	scene->map[i] = 0;
	if (data->game->found_player == 0)
	{
		ft_putstr_fd("Error in map: no player found\n", 2);
		return (1);
	}
	return (0);
}
