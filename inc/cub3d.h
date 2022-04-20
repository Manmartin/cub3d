#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>

# include <mlx.h>

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

#endif