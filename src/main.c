/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:18:56 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/25 19:21:45 by manmarti         ###   ########.fr       */
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
	main_loop(&data);	
	freezers(&data);
	return (0);
}
