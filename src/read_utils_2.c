/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:16:24 by albgarci          #+#    #+#             */
/*   Updated: 2022/06/05 23:17:05 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	*get_line_as_list_element(char *aux_line)
{
	t_line	*l;

	if (!aux_line)
		return (0);
	l = malloc(sizeof(t_line));
	l->next = 0;
	l->line = aux_line;
	return (l);
}
