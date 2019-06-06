#include "queue.h"

int				enqueue(t_queue *queue, void *elem)
{
	t_node		*node;

	if (queue == NULL || (node = node_init(elem)) == NULL)
		return (0);
	if (queue->last == NULL)
		queue->first = node;
	else
		queue->last->next = node;
	queue->last = node;
	return (1);
}
