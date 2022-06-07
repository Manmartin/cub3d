/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:27:38 by manmarti          #+#    #+#             */
/*   Updated: 2022/06/07 13:06:22 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_game_params(t_data *data)
{
	char	player;

	player = data->game->initial_orientation;
	data->game->dir = malloc(sizeof(t_vec));
	data->game->cam = malloc(sizeof(t_vec));
	if (player == 'N')
	{
		*data->game->dir = init_vector(0, -1);
		*data->game->cam = init_vector(0.5, 0);
	}
	else if (player == 'S')
	{
		*data->game->dir = init_vector(0, 1);
		*data->game->cam = init_vector(-0.5, 0);
	}
	else if (player == 'E')
	{
		*data->game->dir = init_vector(1, 0);
		*data->game->cam = init_vector(0, 0.5);
	}
	else
	{
		*data->game->dir = init_vector(-1, 0);
		*data->game->cam = init_vector(0, -0.5);
	}
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
	render(data);
	mlx_loop(data->mlx);
}
