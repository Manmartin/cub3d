/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:21:43 by manmarti          #+#    #+#             */
/*   Updated: 2022/05/31 19:40:59 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*  TEMP FUNCTION 
**	This function will release all reserved memory
*/

int	clean_exit(t_data *data)
{
	freezers(data);
	exit(0);
	return (0);
}
