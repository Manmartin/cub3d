/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:25:17 by manuel            #+#    #+#             */
/*   Updated: 2022/06/07 12:29:19 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

/* Esta funcion va fuera de aqui */

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
			freezers(data);
			ft_putstr_fd("Error\nError loading textures\n", 2);
			exit(1);
		}
		tex->addr = mlx_get_data_addr(tex->img,
				&tex->bits_per_pixel, &tex->line_length, &tex->endian);
	}
}

static t_tex	init_texture(t_vec *player, t_img img, t_ray ray, int side)
{
	t_tex	tex;

	if (side == NORTH || side == SOUTH)
		tex.wall_x = (player->x + 0.5) + ray.length * ray.x;
	else
		tex.wall_x = (player->y + 0.5) + ray.length * ray.y;
	tex.wall_x -= floor(tex.wall_x);
	tex.tex_x = floor(tex.wall_x * (double)(img.width));
	if (side == WEST || side == SOUTH)
		tex.tex_x = img.width - tex.tex_x - 1;
	tex.step = 1.0 * img.height / ray.height;
	tex.tex_pos = (ray.start - HEIGHT / 2 + ray.height / 2) * tex.step;
	return (tex);
}

void	put_texture(t_data	*data, t_ray ray, int side)
{
	t_tex			tex;
	int				y;
	unsigned int	color;
	int				index;

	tex = init_texture(data->game->player, data->scene->tex_img[side],
			ray, side);
	y = -1;
	while (++y < ray.start)
		put_pixel(&data->img, ray.column, y, data->scene->floor_color);
	while (y < ray.end)
	{
		tex.tex_y = tex.tex_pos;
		tex.tex_pos += tex.step;
		index = tex.tex_y * data->scene->tex_img[side].width + tex.tex_x;
		color = ((unsigned int *)(data->scene->tex_img[side].addr))[index];
		put_pixel(&data->img, ray.column, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		put_pixel(&data->img, ray.column, y, data->scene->ceilling_color);
		y++;
	}
}
