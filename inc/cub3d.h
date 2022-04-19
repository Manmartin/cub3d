#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# define BUFFER_SIZE 100

typedef struct s_scene_data
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceilling_color;
	char	**scene;
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

void	freezers(t_data *data);
char	*get_next_line(int fd);
char	*ft_create_line(char **lft);
char	*ft_first_read(int fd, char *lft);
int		ft_read_loop(int fd, char **lft);
int		ft_c(const char *s, int c);

#endif
