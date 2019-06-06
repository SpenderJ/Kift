#include "server.h"

t_content	*content_init(char *key, char *value, uint8_t flag)
{
	t_content	*node;

	if ((node = (t_content *)malloc(sizeof(t_content))) == NULL)
		return (NULL);
	memset(node, 0, sizeof(t_content));
	node->key = key;
	node->value = value;
	node->flag = flag;
	return (node);
}

/*
** Add the key and the value into the queue
** If successful, return 1. Otherwise, a 0 is returned to indicate an error.
*/

int			content_add(t_http *data, char *key, char *value, uint8_t flag)
{
	t_content	*node;

	if (data == NULL)
		return (0);
	if (data->content == NULL)
		data->content = queue_init();
	if ((node = content_init(key, value, flag)) == NULL)
		return (0);
	if (enqueue(data->content, node) == 0)
	{
		content_free(node);
		return (0);
	}
	return (1);
}

/*
** Split the data in two part: key and value
** If successful, return 1. Otherwise, a 0 is returned to indicate an error.
*/

static int	content_split(t_http *data, char *content)
{
	char		*key;
	char		*value;
	uint32_t	i;

	i = 0;
	while (content[i] && content[i] != '=')
		++i;
	if ((key = strndup(content, i)) == NULL)
		return (0);
	content = content + i + 1;
	i = 0;
	while (content[i])
		++i;
	if (i == 0)
		value = NULL;
	else if ((value = strndup(content, i)) == NULL)
		return (0);
	if (content_add(data, key, value, 0) == 0)
		return (0);
	return (1);
}

/*
** Parse the data receive and add it to the queue
** If successful, return 1. Otherwise, a 0 is returned to indicate an error.
*/

int			content_parse(t_http *data, char *content)
{
	int			ret;
	char		*ptr;
	char		*tmp;

	ret = 1;
	tmp = content;
	while ((ptr = strchr(tmp, '&')) != NULL)
	{
		*ptr = '\0';
		if ((ret = content_split(data, tmp)) == 0)
			break ;
		tmp = ptr + 1;
	}
	if (ret != 0 && *tmp != '\0')
		ret = content_split(data, tmp);
	free(content);
	return (ret);
}
