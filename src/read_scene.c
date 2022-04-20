#include "cub3d.h"


int	read_scene(t_scene_data *scene)
{
	get_scene_size(&scene->width, &scene->height);
	parse_map(scene);
	print_map(scene);
	printf("width %li, height %li", scene->width, scene->height);
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
	fd = open("sample.cub", O_RDONLY);
	if (fd < 0)
		perror("error opening scene file");
	while (i < 8)
	{
		get_next_line(fd);
		i++;
	}
	i = 0;
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
		line = get_next_line(fd);
		i++;
	}
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
		get_next_line(fd);
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
		line = get_next_line(fd);
		height++;
	}
	close(fd);
	*scene_width = width;
	*scene_height = height;
}
