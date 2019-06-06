#include "server.h"
#include "response.h"

/*
** Freeing response structure
*/

int					reponse_free(t_reponse *answer)
{
	if (answer == NULL)
		return (0);
	if (answer->complete_path)
		free(answer->complete_path);
	if (answer->content_type)
		free(answer->content_type);
	if (answer->date)
		free(answer->date);
	close(answer->file_fd);
	free(answer);
	return (0);
}

/*
** Free a char * if it exists
** Always return 0
*/

int					ft_free(char *to_free)
{
	if (to_free)
		free(to_free);
	return (0);
}

/*
** Free the queue if exist
*/

static void			queue_content_free(t_queue *queue)
{
	t_node		*tmp;

	if (queue == NULL)
		return ;
	tmp = NULL;
	while (queue->first)
	{
		tmp = queue->first;
		queue->first = queue->first->next;
		content_free(tmp->elem);
		free(tmp);
	}
	free(queue);
}

/*
** Free the content
*/

void				content_free(t_content *node)
{
	if (node == NULL)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

/*
** Free the HTTP Request structure
*/

int					http_free(t_http *data)
{
	if (data == NULL)
		return (1);
	if (data->path)
		free(data->path);
	if (data->accept)
		free(data->accept);
	if (data->boundary)
		free(data->boundary);
	if (data->content)
		queue_content_free(data->content);
	free(data);
	return (1);
}
