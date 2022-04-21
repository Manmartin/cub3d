#include "cub3d.h"

int	read_scene(t_scene_data *scene)
{
	get_scene_size(&scene->width, &scene->height);
	parse_map(scene);
	print_map(scene);
	printf("width %li, height %li", scene->width, scene->height);
	return (0);
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

int		parse_map(t_scene_data *scene)
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

void	get_scene_size(size_t *scene_width, size_t *scene_height)
{
	char	*line;
	int		fd;
	int		i;
	size_t	width;
	size_t	height;

	i = 0;
	height = 0;
	width = 0;
	fd = open("sample.cub", O_RDONLY);
	if (fd < 0)
		perror("error opening scene file");
	while (i < 8)
	{
		line = get_next_line(fd);
		free(line);	
		i++;
	}
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(line) > width)
			width = ft_strlen(line);
		if (width > 0 && line[width - 1] == '\n')
			width--;
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
		height++;
	}
	if (line)
		free(line);
	close(fd);
	*scene_width = width;
	*scene_height = height;
}
