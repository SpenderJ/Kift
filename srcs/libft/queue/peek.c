#include "queue.h"

void			*peek(t_queue *queue)
{
	t_node		*node;

	if (is_empty(queue) == 1)
		return (NULL);
	node = queue->first;
	return (node->elem);
}
