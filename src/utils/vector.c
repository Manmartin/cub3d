/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:36:36 by manuel            #+#    #+#             */
/*   Updated: 2022/05/20 18:16:04 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vec	init_vector(double x, double y)
{
	t_vec	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}

t_vec	rotate_vector(t_vec vec, double angle)
{
	t_vec	new_vector;

	new_vector.x = cos(angle) * vec.x - sin(angle) * vec.y;
	new_vector.y = sin(angle) * vec.x + cos(angle) * vec.y;
	return (new_vector);
}

t_vec	sum_vector(t_vec v1, t_vec v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return (v1);
}
