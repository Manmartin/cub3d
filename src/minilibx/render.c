/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:34:54 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/26 20:32:33 by manuel           ###   ########.fr       */
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

void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	make_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
