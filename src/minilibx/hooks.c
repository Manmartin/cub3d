/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:15:07 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/25 20:42:28 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* Every print in this file have a debug function */

static void	move_x(t_data *data, int mv)
{
	t_vec	*player;

	player = data->game->player;
	if (data->scene->map[(int)player->y][(int)player->x + mv] != '1')
		player->x += mv;
	render(data);
}

static void	move_y(t_data *data, int mv)
{
	t_vec	*player;

	player = data->game->player;
	if (data->scene->map[(int)player->y + mv][(int)player->x] != '1')
		player->y += mv;
	render(data);
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
		move_x(data, 1);
	else if (keycode == KEY_A)
		move_x(data, -1);
	else if (keycode == KEY_W)
		move_y(data, -1);
	else if (keycode == KEY_S)
		move_y(data, 1);
	else if (keycode == KEY_LEFT)
		rotate(data, -1);
	else if (keycode == KEY_RIGHT)
		rotate(data, 1);
	return (keycode);
}
