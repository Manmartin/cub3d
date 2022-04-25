/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:27:38 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/25 19:54:02 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	main_loop(t_data *data)
{
	t_img img;

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 800, 800, "Cub3d");

	img.img = mlx_new_image(data->mlx, 800,  800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	data->img = img;
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win, 2, 1L, keys_hook, data);
	mlx_hook(data->win, 17, 0, clean_exit, data);

	render(data);
	mlx_loop(data->mlx);
}
