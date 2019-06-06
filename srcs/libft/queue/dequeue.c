#include "queue.h"

void				*dequeue(t_queue *queue)
{
	void			*elem;
	t_node			*node;

	if (is_empty(queue) == 1)
		return (NULL);
	node = queue->first;
	queue->first = node->next;
	if (queue->last == node)
		queue->last = NULL;
	elem = node->elem;
	free(node);
	return (elem);
}
