#include "cub3d.h"

int	parse_colors_2(char *line)
{
	int		sep_rgb[3];
	char	*aux;
	int		color;

	aux = line + 2;
	if (!aux || ft_strlen(aux) == 0 || *(aux) == ',')
		return (-1);
	sep_rgb[0] = ft_atoi(aux);
	aux = ft_strchr(aux, ',');
	if (!aux || ft_strlen(aux) <= 1 || *(++aux) == ',')
		return (-1);
	sep_rgb[1] = ft_atoi(aux);
	aux = ft_strchr(aux, ',');
	if (!aux || ft_strlen(aux) <= 2)
		return (-1);
	sep_rgb[2] = ft_atoi(++aux);
	color = ((sep_rgb[0] << 16) | (sep_rgb[1] << 8) | sep_rgb[2]);
	return (color);
}

int	parse_colors(t_scene_data *scene, t_line *l)
{
	if (ft_strncmp(l->line, "F ", 2) == 0)
	{
		scene->floor_color = parse_colors_2(l->line);
		if (scene->floor_color == -1)
			return (1);
	}
	else
		return (1);
	l = l->next;
	if (ft_strncmp(l->line, "C ", 2) == 0)
	{
		scene->ceilling_color = parse_colors_2(l->line);
		if (scene->ceilling_color == -1)
			return (1);
	}
	else
		return (1);
//	printf("color ok\n");
//	printf("%u, %u\n", scene->floor_color, scene->ceilling_color);
	l = l->next;
	return (0);
}
