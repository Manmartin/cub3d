/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:34:54 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/25 20:13:38 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_sqrt(int x, int y, int size, t_img *img)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			put_pixel(img, x + j, y + i, 255);
}


void	render(t_data *data)
{
	(void)data;
	mlx_clear_window(data->mlx, data->win);
	put_sqrt(10, 10, 50, &data->img);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
