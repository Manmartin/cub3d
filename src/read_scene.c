#include "cub3d.h"

int	read_scene(t_data *data,t_scene_data *scene)
{
	copy_map(scene);
	(void) data;
	get_scene_size(scene->scene_list, &scene->width, &scene->height);
//	parse_map(data, scene);
//	print_map(scene);
	printf("width %li, height %li", scene->width, scene->height);
	return (0);
}

t_line	*get_line_as_list_element(char *aux_line)
{
	t_line *l;

	l = malloc(sizeof(t_line));
	l->next = 0;
	l->line = aux_line;
	return (l);
}

int	copy_map(t_scene_data *scene)
{
	int		fd;
	t_line 	*l;
	char	*aux_line;

	l = 0;
	fd = open(scene->scene_path, O_RDONLY);
	if (fd < 1)
		perror("error opening scene file");
	scene->scene_list = malloc(sizeof(t_line *));
	aux_line = get_next_line(fd);
	if (aux_line)
	{
		l = get_line_as_list_element(aux_line);
		*(scene->scene_list) = l;
	}
	aux_line = get_next_line(fd);
	while (aux_line)
	{
		l->next = get_line_as_list_element(aux_line);
		l = l->next;
		printf("%s", l->line);
		aux_line = get_next_line(fd);
	}
	l = *(scene->scene_list);
//	printf("%s\n", l->line);
/*	while (l)
	{
		printf("%s", l->line);
		l = l->next;
	}
	*/
	close(fd);
	return (1);
}

int	parse_colors(t_scene_data *scene, int fd)
{
	int		sep_rgb[3];
	char	*line;
	char	*aux;

	line = get_next_line(fd);
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		aux = line + 2;
		sep_rgb[0] = ft_atoi(aux);
		aux = ft_strchr(aux, ',') + 1;
		sep_rgb[1] = ft_atoi(aux);
		aux = ft_strchr(aux, ',') + 1;
		sep_rgb[2] = ft_atoi(aux);
		scene->floor_color = ((sep_rgb[0] << 16) | (sep_rgb[1] << 8) | sep_rgb[2]);
		free(line);
	}
	else
		return (1);
	line = get_next_line(fd);
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		aux = line + 2;
		sep_rgb[0] = ft_atoi(aux);
		aux = ft_strchr(aux, ',') + 1;
		sep_rgb[1] = ft_atoi(aux);
		aux = ft_strchr(aux, ',') + 1;
		sep_rgb[2] = ft_atoi(aux);
		scene->ceilling_color = ((sep_rgb[0] << 16) | (sep_rgb[1] << 8) | sep_rgb[2]);
		free(line);
	}
	else
		return (1);
	printf("%u, %u\n", scene->floor_color, scene->ceilling_color);
	return (0);
}

int		parse_texture_paths(t_scene_data *scene, int fd)
{
	size_t	i;
	char	*line;
	char	*aux;

	scene->cardinal[0] = ft_strdup("NO ");
	scene->cardinal[1] = ft_strdup("SO ");
	scene->cardinal[2] = ft_strdup("WE ");
	scene->cardinal[3] = ft_strdup("EA ");
	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		aux = line;
		if (ft_strncmp(aux, scene->cardinal[i], 3) == 0)
		{
			aux += 3;
			scene->textures[i] = ft_substr(aux, 0, ft_strchr(aux, '\n') - aux);
			free(line);
		}
		else
		{
			free(line);
			return (1);
		}
		i++;
	}
	line = get_next_line(fd);
	free(line);
	return (0);
}

int		parse_map(t_data *data, t_scene_data *scene)
{
	size_t	i;
	size_t	j;
	size_t	fd;
	char	*line;

	i = 0;
	j = 0;
	fd = open(scene->scene_path, O_RDONLY);
	if (fd < 0)
		perror("error opening scene file");
	if (parse_texture_paths(scene, fd) == 1)
	{
		ft_putstr_fd("Error parsing texture paths\n", 2);
		return (1);
	}
	parse_colors(scene, fd);
	line = get_next_line(fd);
	free(line);
	scene->map = malloc(sizeof(char *) * (scene->height + 1));
	line = get_next_line(fd);
	while (line)
	{
		scene->map[i] = malloc(sizeof(char) * scene->width + 1);
		while (j < ft_strlen(line) - 1)
		{
			scene->map[i][j] = line[j];
			if (line[j] == 'N')
			{
				data->game->player->x = j;
				data->game->player->y = i;
				printf("[%f %f]\n", data->game->player->x, data->game->player->y);
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
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (line)
		free(line);
	scene->map[i] = 0;
	close(fd);
	return (0);
}

void	get_scene_size(t_line **raw_scene, size_t *scene_width, size_t *scene_height)
{
	int		i;
	t_line	*l;

	i = 0;
	*scene_height = 0;
	*scene_width = 0;
	l = *raw_scene;
	while (i < 8)
	{
		l = l->next;
		i++;
	}
	while (l)
	{
		if (ft_strlen(l->line) > *scene_width)
			*scene_width = ft_strlen(l->line);
		if (*scene_width > 0 && l->line[*scene_width - 1] == '\n')
			*scene_width -= 1;
		printf("%s", l->line);
		l = l->next;
		(*scene_height) += 1;
	}
}
