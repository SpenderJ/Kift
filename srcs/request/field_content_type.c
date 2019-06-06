#include "server.h"

static int		boundary(char *str, t_http *data)
{
	if (*str == ';')
		++str;
	while (*str && *str == ' ')
		++str;
	if (strncmp(str, "boundary=", 9) == 0)
	{
		if ((data->boundary = concat("--", str + 9)) == NULL)
			return (0);
		return (1);
	}
	return (0);
}

int				field_content_type(char *str, t_http *data)
{
	int8_t					i;
	static t_lookup			type[POST_NUMBER] = {
		{"text/plain", 10, POST_TYPE_1},
		{"application/x-www-form-urlencoded", 33, POST_TYPE_2},
		{"multipart/form-data", 19, POST_TYPE_3},
	};

	if (data->method != METHOD_POST)
		return (0);
	while (*str && *str == ' ')
		++str;
	i = 0;
	while (i < POST_NUMBER)
	{
		if (strncmp(str, type[i].name, type[i].length) == 0)
		{
			data->content_type = type[i].number;
			if (type[i].number == POST_TYPE_3)
				return (boundary(str + type[i].length, data));
			return (1);
		}
		++i;
	}
	return (0);
}
