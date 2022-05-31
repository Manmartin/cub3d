/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:34:54 by manmarti          #+#    #+#             */
/*   Updated: 2022/05/31 17:53:58 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	ray_casting(t_data *data)
{
	double	cam_vec;
	t_ray	ray;

	ray.column = -1;
	while (++ray.column < WIDTH)
	{
		cam_vec = ray.column * 2 / (double)WIDTH - 1;
		ray.x = data->game->dir->x + data->game->cam->x * cam_vec;
		ray.y = data->game->dir->y + data->game->cam->y * cam_vec;
		if (ray.x != 0)
			ray.delta.x = fabs(1 / ray.x);
		else
			ray.delta.x = HUGE_VAL;
		if (ray.y != 0)
			ray.delta.y = fabs(1 / ray.y);
		else
			ray.delta.y = HUGE_VAL;
		cast_ray(ray, data);
	}
}

void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
