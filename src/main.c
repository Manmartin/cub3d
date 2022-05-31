/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:18:56 by manmarti          #+#    #+#             */
/*   Updated: 2022/05/31 17:54:53 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Usage ./cub3d scene.cub\n", 1);
		return (0);
	}
	data.scene = malloc(sizeof(t_scene_data));
	data.scene->scene_path = argv[1];

	data.game = ft_calloc(1, sizeof(t_game));
	data.game->player = ft_calloc(1, sizeof(t_vec));
	data.game->dir = ft_calloc(1, sizeof(t_vec));
	read_scene(&data,data.scene);
	data.scene->valid_map = 1;
	if (check_valid_map(data.game->player->x, data.game->player->y, data.scene->map, data.scene) == -1)
		ft_putstr_fd("--------->>>>> bad map <<<<-------\n", 2);
	print_map(data.scene);
	main_loop(&data);
	freezers(&data);
//	system("leaks cub3d");
	return (0);
}
