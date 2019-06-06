#include "server.h"

int				field_accept(char *str, t_http *data)
{
	while (*str && *str == ' ')
		++str;
	if ((data->accept = strdup(str)) == NULL)
		return (0);
	return (1);
}
