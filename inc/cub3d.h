#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# define BUFFER_SIZE 100

typedef struct s_scene_data
{
	char	*scene_path;
	char	*textures[4];
	char	*cardinal[4];
	unsigned int		floor_color;
	unsigned int		ceilling_color;
	char	**map;
	size_t	width;
	size_t	height;
}	t_scene_data;

typedef struct s_data
{
	t_scene_data	*scene;

}	t_data;

//read_scene.c
int		read_scene(t_scene_data *scene);
void	get_scene_size(size_t *scene_width, size_t *scene_height);
int		parse_map(t_scene_data *scene);

//temporary_utils.c
void	print_map(t_scene_data *scene);

void	freezers(t_data *data);
char	*get_next_line(int fd);
char	*ft_create_line(char **lft);
char	*ft_first_read(int fd, char *lft);
int		ft_read_loop(int fd, char **lft);
int		ft_c(const char *s, int c);

#endif
