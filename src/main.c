/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:52:02 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/20 17:27:33 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* WARNING, this is a temp main file, do not include it in main branch */

int	main(void)
{
	t_data	data;
	t_img	img;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(data.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	mlx_key_hook(data.win, keys_hook, &data);
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
	mlx_loop(data.mlx);
}
