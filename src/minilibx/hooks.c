/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:15:07 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/26 20:01:58 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* Every print in this file have a debug function */

static void	move(t_data *data, double angle)
{
	t_vec	new_coords;
	t_vec	tmp_dir;

	tmp_dir = rotate_vector(*data->game->dir, angle);
	new_coords = sum_vector(*data->game->player, tmp_dir);
	new_coords.x = round(new_coords.x);
	new_coords.y = round(new_coords.y);
	if (data->scene->map[(int)new_coords.y][(int)new_coords.x] != '1')
	{
		data->game->player->x = new_coords.x;
		data->game->player->y = new_coords.y;
		render(data);
	}
}

static void	rotate(t_data *data, int mv)
{
	printf("Rotate: %i\n", mv);
	(void)data;
	(void)mv;
}

int	keys_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESCAPE)
		clean_exit(data);
	else if (keycode == KEY_D)
		move(data, M_PI_2);
	else if (keycode == KEY_A)
		move(data, -M_PI_2);
	else if (keycode == KEY_W)
		move(data, 0);
	else if (keycode == KEY_S)
		move(data, M_PI);
	else if (keycode == KEY_LEFT)
		rotate(data, -1);
	else if (keycode == KEY_RIGHT)
		rotate(data, 1);
	return (keycode);
}
