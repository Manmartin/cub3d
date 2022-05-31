/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:25:17 by manuel            #+#    #+#             */
/*   Updated: 2022/05/31 17:24:18 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	load_textures(t_data *data)
{
	int		i;
	t_img	*tex;

	i = -1;
	while (++i < 4)
	{
		tex = &data->scene->tex_img[i];
		tex->img = mlx_xpm_file_to_image(data->mlx, data->scene->textures[i],
			&tex->width, &tex->height);
		if (!tex->img)
		{
			printf("Error\n");
			exit(0);
		}
		tex->addr = mlx_get_data_addr(tex->img, 
			&tex->bits_per_pixel, &tex->line_length, &tex->endian);
	}
}

void	put_texture(t_data	*data, t_ray ray, int side)
{
	t_vec	*player;
	t_img	img;
	double	wallX;
	int		texX;

	player = data->game->player;
	img = data->scene->tex_img[side];
	if (side == NORTH || side == SOUTH)
		wallX = (player->x + 0.5) + ray.length * ray.x;
	else
		wallX = (player->y + 0.5) + ray.length * ray.y;
	wallX -= floor(wallX);
	texX = floor(wallX * (double)(img.width));
	if (side == EAST || side == NORTH)
		texX = img.width - texX - 1;
	double	step;

	step = 1.0 * img.height / ray.height;

	double	texPos;
	texPos = (ray.start - HEIGHT / 2 + ray.height / 2) * step;
	unsigned int color;

	int y;

	y = -1;
	while (++y < ray.start)
		put_pixel(&data->img, ray.column, y, data->scene->floor_color);
	while (y < ray.end)
	{
		int texY = (int)texPos & (img.height - 1);
		texPos += step;
		int index = texY * img.width  + texX;
		color = ((unsigned int *)(img.addr))[index];
		put_pixel(&data->img, ray.column, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
	put_pixel(&data->img, ray.column, y, data->scene->ceilling_color);
		y++;
	}
	
}
