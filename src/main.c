#include "cub3d.h"

int main(void)
{
	t_data	data;

	data.scene = malloc(sizeof(t_scene_data));
	read_scene(data.scene);

	freezers(&data);
	return (0);
}
