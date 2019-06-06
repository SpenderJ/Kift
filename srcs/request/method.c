#include "server.h"

static uint8_t		method_protocol(char *method, t_http *data)
{
	if (*method == '\0' || strncmp(method, "HTTP/", 5) != 0)
		return (0);
	method = method + 5;
	if (strncmp("1.0", method, 3) == 0)
		data->protocol = PROTOCOL_1_0;
	else if (strncmp("1.1", method, 3) == 0)
		data->protocol = PROTOCOL_1_1;
	else if (strncmp("2.0", method, 3) == 0)
		data->protocol = PROTOCOL_2_0;
	else
		return (0);
	return (1);
}

static uint8_t		method_path(char *method, t_http *data)
{
	uint32_t	i;
	uint32_t	len;

	i = 0;
	while (method[i] && method[i] != ' ')
		++i;
	if (method[i] == '\0')
		return (0);
	++i;
	len = 0;
	while (method[i + len] && method[i + len] != ' ')
		++len;
	data->path = strndup(&method[i], len);
	if (method_protocol(method + i + len + 1, data) == 0)
		return (0);
	return (1);
}

uint8_t				method(char *method, t_http *data)
{
	uint8_t			i;
	static t_lookup	m[METHOD_NUMBER] = {
		{"GET", 3, METHOD_GET},
		{"HEAD", 4, METHOD_HEAD},
		{"POST", 4, METHOD_POST},
		{"PUT", 3, METHOD_PUT}
	};

	i = 0;
	while (i < METHOD_NUMBER)
	{
		if (strncmp(method, m[i].name, m[i].length) == 0)
		{
			data->method = m[i].number;
			method_path(method, data);
			return (1);
		}
		++i;
	}
	return (0);
}
