#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Usage ./cub3d scene.cub", 1);
		return (0);
	}
	data.scene = malloc(sizeof(t_scene_data));
	data.scene->scene_path = argv[1];
	read_scene(data.scene);

	freezers(&data);
//	system("leaks cub3d");
	return (0);
}
