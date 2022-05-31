/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:27:38 by manmarti          #+#    #+#             */
/*   Updated: 2022/05/31 17:10:25 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_game_params(t_data *data)
{
	data->game->dir = malloc(sizeof(t_vec));
	data->game->cam = malloc(sizeof(t_vec));
	data->game->dir->x = 0;
	data->game->dir->y = -1;
	data->game->cam->x = 0.5;
	data->game->cam->y = 0;
}

void	main_loop(t_data *data)
{
	t_img	img;

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
	img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	data->img = img;
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win, 2, 1L, keys_hook, data);
	mlx_hook(data->win, 17, 0, clean_exit, data);
	load_textures(data);
	init_game_params(data);
	//mlx_put_image_to_window(data->mlx, data->win, data->scene->tex_img[3].img,0,0);
	render(data);
	mlx_loop(data->mlx);
}
