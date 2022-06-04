#include "cub3d.h"

int	read_scene(t_data *data,t_scene_data *scene)
{
	if (copy_map(scene))
		return (1);
//	(void) data;
	if (check_input_schema(scene))
		return (1);
	if (get_scene_size(scene, &scene->width, &scene->height))
	{
		ft_putstr_fd("Wrong map\n", 2);
		return (1);
	}
	if (parse_scene(data, scene))
		return (1);
//	print_map(scene);
//	printf("width %li, height %li", scene->width, scene->height);
	return (0);
}

int	copy_map(t_scene_data *scene)
{
	int		fd;
	t_line 	*l;
	char	*aux_line;

	l = 0;
	fd = open(scene->scene_path, O_RDONLY);
	if (fd < 1)
	{
		perror("error opening scene file");
		return (1);
	}
	aux_line = get_next_line(fd);
	if (!aux_line)
	{
		ft_putstr_fd("Empty map\n", 2);
		return (1);
	}
	scene->scene_list = malloc(sizeof(t_line *));
	l = get_line_as_list_element(aux_line);
	*(scene->scene_list) = l;
	while (aux_line)
	{
		aux_line = get_next_line(fd);
		l->next = get_line_as_list_element(aux_line);
		l = l->next;
	}
	close(fd);
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
		//freezers?
		ft_putstr_fd("Error parsing texture paths\n", 2);
		return (1);
	}
	if (check_texture_names(scene) == 1)
	{
		//freezers?
		return (1);
	}
	if (parse_colors(scene, scene->colors_start))
	{
		//freezers?
		ft_putstr_fd("Error parsing colors, invalid map\n", 2);
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
