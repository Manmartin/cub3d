/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:27:38 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/23 18:33:52 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	main_loop(t_data *data)
{
	t_img	img;

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1920, 1080, "Cub3d");
	img.img = mlx_new_image(data->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	mlx_key_hook(data->win, keys_hook, &data);
	mlx_hook(data->win, 17, 0L, clean_exit, &data);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_loop(data->mlx);
}
