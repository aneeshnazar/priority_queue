#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HIPRIORITY(a, b) (a < b)
#define LOPRIORITY(a, b) (a > b)

typedef struct  data {
    int value;
}               t_data;

typedef struct  node {
    t_data      data;
    int         priority;
    struct node *next;
}               t_node;

typedef struct  p_queue {
    t_node      *max_p;
    t_node      *min_p;
}               t_queue;

t_data  init_data(int val)
{
    t_data  dat;

    dat.value = val;
    return (dat);
}

t_queue	*init(void)
{
	t_queue	*new;

	new = (t_queue *)malloc(sizeof(t_queue));
	new->max_p = NULL;
	new->min_p = NULL;
	return (new);
}

t_node  *init_node(t_data data, int priority)
{
    t_node  *new;

    new = (t_node *)malloc(sizeof(t_node));
    new->data = data;
    new->priority = priority;
    new->next = NULL;
    return (new);
}

void			enqueue(t_queue *queue, t_data num, int priority)
{
	t_node	*new;
    t_node  *tmp;

    new = init_node(num, priority);
	if (!queue->max_p)
		queue->max_p = new;
	if (!queue->min_p)
		queue->min_p = new;
	else
	{
        if (LOPRIORITY(queue->min_p->priority, priority))
        {
            queue->min_p->next = new;
    		queue->min_p = queue->min_p->next;
        }
        else if (HIPRIORITY(queue->max_p->priority, priority))
        {
            new->next = queue->max_p;
    		queue->max_p = new;
        }
        else
        {
            tmp = queue->max_p;
            while (tmp && LOPRIORITY(tmp->priority, priority))
            {
                tmp = tmp->next;
            }
            new->next = tmp;
            tmp->next = new;
        }
	}
}

t_data			dequeue(t_queue *queue)
{
	t_node	*tmp;
	t_data			tmp_num;

	if (!queue->max_p)
		return (init_data(0));
	tmp = queue->max_p;
	tmp_num = queue->max_p->data;
	queue->max_p = queue->max_p->next;
	if (!queue->max_p)
		queue->min_p = NULL;
	free(tmp);
	tmp = NULL;
	return (tmp_num);
}

t_data			peek(t_queue *queue)
{
	if (!queue->max_p)
		return (init_data(0));
	return (queue->max_p->data);
}

int				isEmpty(t_queue *queue)
{
	return (!queue->max_p && !queue->min_p);
}

int main(void)
{
    t_data dat[8];

    dat[0] = init_data(8);
    dat[1] = init_data(3);
    dat[2] = init_data(6);
    dat[3] = init_data(5);
    dat[4] = init_data(9);
    dat[5] = init_data(7);
    dat[6] = init_data(2);
    dat[7] = init_data(1);

    t_queue *q;
    q = init();
    for (size_t i = 0; i < 8; i++) {
        enqueue(q, dat[i], i);
    }
    while(!isEmpty(q)){
        t_data tmp = dequeue(q);
        printf("Value: %d\n", tmp.value);
    }
    return 0;
}
