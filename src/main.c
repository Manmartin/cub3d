/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:18:56 by manmarti          #+#    #+#             */
/*   Updated: 2022/07/01 18:42:10 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	main_starters(t_data *data, char **argv)
{
	data->scene = malloc(sizeof(t_scene_data));
	data->scene->scene_path = argv[1];
	data->game = ft_calloc(1, sizeof(t_game));
	data->game->player = ft_calloc(1, sizeof(t_vec));
	data->game->player->x = 0;
	data->game->player->y = 0;
	data->game->found_player = 0;
	data->scene->valid_map = 1;
}

static int	name_checker(char *str)
{		
	char	*aux;

	if (ft_strlen(str) <= 4)
	{
		ft_putstr_fd("Error\nBad file extension: only .cub allowed\n", 2);
		return (1);
	}
	aux = str + ft_strlen(str) - 4;
	if (ft_strncmp(".cub", aux, 4) != 0)
	{
		ft_putstr_fd("Error\nBad file extension: only .cub allowed\n", 2);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage ./cub3d scene.cub\n", 2);
		return (1);
	}
	if (name_checker(argv[1]))
		return (1);
	main_starters(&data, argv);
	if (read_scene(&data, data.scene))
		return (1);
	check_valid_map(data.game->player->x,
		data.game->player->y, data.scene->map, data.scene);
	if (data.scene->valid_map == 0)
	{
		ft_putstr_fd("Error\nWrong map\n", 2);
		freezers(&data);
		return (1);
	}
	main_loop(&data);
	return (0);
}
