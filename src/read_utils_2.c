#include "cub3d.h"

t_line	*get_line_as_list_element(char *aux_line)
{
	t_line *l;

	if (!aux_line)
		return (0);
	l = malloc(sizeof(t_line));
	l->next = 0;
	l->line = aux_line;
	return (l);
}
