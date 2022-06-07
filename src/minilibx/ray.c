/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:25:54 by manuel            #+#    #+#             */
/*   Updated: 2022/06/07 11:20:40 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	draw_line(t_data *data, t_ray ray, int side)
{
	put_texture(data, ray, side);
	if (side == 1 && ray.y < 0)
		put_texture(data, ray, NORTH);
	else if (side == 1)
		put_texture(data, ray, SOUTH);
	else if (side == 0 && ray.x > 0)
		put_texture(data, ray, EAST);
	else
		put_texture(data, ray, WEST);
}

static t_ray	ray_length(t_ray ray, int side)
{
	if (side == 0)
		ray.length = ray.side_dist.x - ray.delta.x;
	else
		ray.length = ray.side_dist.y - ray.delta.y;
	ray.height = (int)(HEIGHT / ray.length);
	ray.start = -ray.height / 2 + HEIGHT / 2;
	if (ray.start < 0)
		ray.start = 0;
	ray.end = ray.height / 2 + HEIGHT / 2;
	if (ray.end >= HEIGHT)
		ray.end = HEIGHT - 1;
	return (ray);
}

static	t_ray	ray_movement(t_ray ray)
{
	ray.side_dist.x = 0.5 * ray.delta.x;
	ray.side_dist.y = 0.5 * ray.delta.y;
	if (ray.x < 0)
		ray.step_x = -1;
	else
		ray.step_x = 1;
	if (ray.y < 0)
		ray.step_y = -1;
	else
		ray.step_y = 1;
	return (ray);
}

void	cast_ray(t_ray ray, t_data *data)
{
	t_vec	map;

	map.x = data->game->player->x;
	map.y = data->game->player->y;
	ray = ray_movement(ray);
	while (true)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta.x;
			map.x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist.y += ray.delta.y;
			map.y += ray.step_y;
			ray.side = 1;
		}
		if (data->scene->map[(int)map.y][(int)map.x] == '1')
			break ;
	}
	ray = ray_length(ray, ray.side);
	draw_line(data, ray, ray.side);
}
