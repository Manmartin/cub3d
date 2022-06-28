/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:24:49 by manmarti          #+#    #+#             */
/*   Updated: 2022/06/28 20:29:33 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# include <mlx.h>
# include <math.h>
# include <macros.h>

# define BUFFER_SIZE 100
# define WIDTH 800
# define HEIGHT 800

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

typedef struct s_vec {
	double	x;
	double	y;
}	t_vec;

typedef struct s_ray
{
	int		column;
	double	x;
	double	y;

	t_vec	delta;
	t_vec	side_dist;
	int		side;

	double	length;
	int		start;
	int		end;
	int		height;

	int		step_x;
	int		step_y;

}	t_ray;

typedef struct s_tex
{
	double	wall_x;
	double	tex_pos;
	double	step;
	int		tex_x;
	int		tex_y;
}	t_tex;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_line
{
	char			*line;	
	struct s_line	*next;	
}	t_line;

typedef struct s_scene_data
{
	char	*scene_path;
	t_line	**scene_list;
	t_line	*colors_start;
	t_line	*map_start;
	char	*textures[4];
	t_img	tex_img[4];
	char	*cardinal[4];
	int		floor_color;
	int		ceilling_color;
	char	**map;
	long	width;
	long	height;
	int		all_elements;
	char	**elements;
	int		valid_map;
}	t_scene_data;

typedef struct s_game {
	t_vec	*player;
	t_vec	*dir;
	t_vec	*cam;
	int		found_player;
	char	initial_orientation;
}	t_game;

typedef struct s_data
{
	t_scene_data	*scene;
	void			*mlx;
	void			*win;
	t_img			img;
	t_game			*game;

}	t_data;

//read_scene.c
int		read_scene(t_data *data, t_scene_data *scene);
int		copy_map(t_scene_data *scene);
int		read_scene(t_data *data, t_scene_data *scene);
int		get_scene_size(t_scene_data *scene, long *scene_width,
			long *scene_height);
int		parse_scene(t_data *data, t_scene_data *scene);
int		parse_texture_paths(t_scene_data *scene, t_line *l);

//read_checks_1.c
int		check_texture_names(t_scene_data *scene);
int		check_input_schema(t_scene_data *scene);

//read_colors.c
int		parse_colors(t_scene_data *scene, t_line *l);
int		parse_colors_2(char *line);

//read_utils_2.c
t_line	*get_line_as_list_element(char *aux_line);

//temporary_utils.c
void	print_map(t_scene_data *scene);

void	freezers(t_data *data);
char	*get_next_line(int fd);
char	*ft_create_line(char **lft);
char	*ft_first_read(int fd, char *lft);
int		ft_read_loop(int fd, char **lft);
int		ft_c(const char *s, int c);

/* minilibx */
void	main_loop(t_data *data);
int		keys_hook(int keycode, t_data *data);
void	render(t_data *data);
void	put_pixel(t_img *img, int x, int y, int color);
void	load_textures(t_data *data);
void	put_texture(t_data	*data, t_ray ray, int side);

/* ray.c */
void	cast_ray(t_ray ray, t_data *data);
/* check_map.c */
int		check_valid_map(long x, long y, char **map, t_scene_data *scene);

/* freezers */
void	free_raw_scene(t_scene_data *scene);
int		free_cardinals(t_scene_data *scene);
int		free_textures(t_scene_data *scene);
void	free_basics(t_data *data, t_scene_data *scene);
void	free_map(t_scene_data *scene);
void	free_map_partially(t_scene_data *scene, int limit);

/* utils */
int		clean_exit(t_data *data);
t_vec	init_vector(double x, double y);
t_vec	sum_vector(t_vec v1, t_vec v2);
t_vec	rotate_vector(t_vec vec, double angle);

#endif
