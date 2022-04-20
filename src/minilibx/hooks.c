/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:15:07 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/20 17:27:55 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	keys_hook(int keycode, t_data *data)
{
	(void)data;
	printf("Key number = %i\n", keycode);
	return (keycode);
}
