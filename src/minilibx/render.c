/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:34:54 by manmarti          #+#    #+#             */
/*   Updated: 2022/05/19 16:49:06 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_sqrt(int x, int y, int size, int color, t_img *img)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			put_pixel(img, x + j, y + i, color);
}


void	make_map(t_data *data)
{
	int size;
	size_t coorx;
	size_t coory;
	int color;
	t_vec *player;
	t_scene_data *s;

	s = data->scene;
	size = 80;


	player = data->game->player;
	for (int i = -4; i <= 5; i++)
	{
		for (int j = -4; j <= 5;j++)
		{
			coorx = player->x + j;
			coory = player->y + i;
			if (coorx >= s->width || coorx < 0 || coory >= s->height || coory < 0)
				put_sqrt((j + 4) * 80, (i + 4) * 80, 80, 0, &data->img);
			else 
			{
				color = (s->map[coory][coorx] == '1' ? 255 : 255 << 8);
				put_sqrt((j + 4) * 80, (i + 4) * 80, 80, color, &data->img);
			}
		}
	}
	put_sqrt(4 * 80,  4 * 80, 80, 255 << 16, &data->img);
	put_sqrt((4  + (int)data->game->dir->x) * 80,  (4  + (int)data->game->dir->y) * 80, 80, 255 << 8 | 110 << 16 | 209, &data->img);

}

/* Maths!*/

static void	draw_line(t_data *data, int start, int end, int x, int side)
{
	int	y;

	y = -1;
	while (++y < start)
		put_pixel(&data->img, x, y,  135 << 16 | 206 << 8 | 235);
	while (y >= start && y <= end)
	{
		if (side == 0)
			put_pixel(&data->img, x, y, 255);
		else
			put_pixel(&data->img, x, y, 255 << 8);
		y++;
	}
	while (y < 800)
	{
		put_pixel(&data->img, x, y, 188 << 16 | 129 << 8 | 95);
		y++;
	}
}

static void	next_step(t_vec delta, t_vec ray, t_data *data, int x)
{
	int 	step_x;
    int 	step_y;
	int 	side;
	t_vec	side_dist;
	int		map_x;
	int		map_y;
	double	length;

	map_x = data->game->player->x;
	map_y = data->game->player->y;
	side_dist.x = 0.5 * delta.x;
	side_dist.y = 0.5 * delta.y;
	if (ray.x < 0)
		step_x = -1;
	else
		step_x = 1;
	if (ray.y < 0)
		step_y = -1;
	else
		step_y = 1;
	
	while (true)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta.x;
			map_x+= step_x;
			side = 0;
		}
		else
		{
			side_dist.y += delta.y;
			map_y += step_y;
			side = 1;
		}
		if (data->scene->map[map_y][map_x] == '1')
			break;
	}
	
	if (side == 0)
		length = side_dist.x - delta.x;
	else
		length = side_dist.y - delta.y;
	int lineHeight = (int)(800 / length);	
	int drawStart = -lineHeight / 2 + 800 / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + 800 / 2;
	if (drawEnd >= 800)
		drawEnd = 799;
	draw_line(data, drawStart, drawEnd, x, side);
}

static void	ray_casting(t_data *data)
{
	int 	width;
	double	cam_vec;
	t_vec	ray;
	t_vec	delta;

	width = 800;
	for (int x = 0; x < 800; x++)
	{
		cam_vec = x * 2 / (double)width - 1;
		ray.x = data->game->dir->x + data->game->cam->x * cam_vec;
		ray.y = data->game->dir->y + data->game->cam->y * cam_vec;

		if (ray.x != 0)
			delta.x = fabs(1 / ray.x);
		else
			delta.x = HUGE_VAL;
		if (ray.y != 0)
			delta.y = fabs(1 / ray.y);
		else
			delta.y = HUGE_VAL;
		next_step(delta, ray, data, x);
	}
}


void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	ray_casting(data);
	//make_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
