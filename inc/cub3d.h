/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:28:55 by manmarti          #+#    #+#             */
/*   Updated: 2022/04/23 18:14:07 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# include <mlx.h>
# include <macros.h>

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_data {
	void	*mlx;
	void	*win;
}				t_data;

/* hooks.c */
int		keys_hook(int keycode, t_data *data);

/* utils.c */
int		clean_exit(t_data *data);

#endif