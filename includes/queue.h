#ifndef QUEUE_H
# define QUEUE_H

# include <stdlib.h>

typedef struct		s_node
{
	void			*elem;
	struct s_node	*next;
}					t_node;

typedef struct		s_queue
{
	struct s_node	*first;
	struct s_node	*last;
}					t_queue;

t_queue				*queue_init(void);
t_node				*node_init(void *elem);
void				*peek(t_queue *queue);
void				*dequeue(t_queue *queue);
int					enqueue(t_queue *queue, void *elem);
int					is_empty(t_queue *queue);

#endif
