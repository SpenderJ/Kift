#include "server.h"

static t_http		*http_init(void)
{
	t_http	*data;

	if ((data = (t_http *)malloc(sizeof(t_http))) == NULL)
		return (NULL);
	memset(data, 0, sizeof(t_http));
	return (data);
}

static uint32_t		header_next(char *str)
{
	uint32_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\r' && str[i + 1] == '\n')
		{
			str[i] = '\0';
			str[i + 1] = '\0';
			return (i + 2);
		}
		++i;
	}
	return (i);
}

t_http				*header(int fd, char *request, int *status)
{
	uint32_t	index;
	t_http		*data;

	if (request == NULL)
		return (NULL);
	if ((data = http_init()) == NULL)
	{
		*status = response_error(fd, NULL, INTERNAL_SERVER_ERROR);
		return (NULL);
	}
	data->fd = fd;
	index = header_next(request);
	if (method(request, data) == 0)
	{
		*status = response_error(fd, data, NOT_IMPLEMENTED);
		return (NULL);
	}
	request = request + index;
	while (*request)
	{
		index = header_next(request);
		fields_dispatch(request, data);
		request = request + index;
	}
	return (data);
}
