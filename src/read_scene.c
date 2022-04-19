#include "cub3d.h"
#include <stdio.h>

int	read_scene(t_scene_data *scene)
{
	get_scene_size(&scene->width, &scene->height);
	printf("width %li, height %li", scene->width, scene->height);
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
		printf("%s", line);
		line = get_next_line(fd);
		height++;
	}
	close(fd);
	*scene_width = width;
	*scene_height = height;
}
