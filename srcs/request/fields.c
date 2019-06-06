#include "server.h"

uint8_t		fields_dispatch(char *str, t_http *data)
{
	int8_t				i;
	size_t				len;
	static t_fields		fields[FIELDS_COUNT] = {
		{"Accept:", &field_accept},
		{"Content-Length:", &field_content_length},
		{"Content-Type:", &field_content_type},
		{"Expect:", &field_expect},
		{"Host:", &field_host},
	};

	i = 0;
	while (i < FIELDS_COUNT)
	{
		len = strlen(fields[i].name);
		if (strncmp(str, fields[i].name, len) == 0)
		{
			fields[i].fct(str + len, data);
			return (1);
		}
		++i;
	}
	return (0);
}
