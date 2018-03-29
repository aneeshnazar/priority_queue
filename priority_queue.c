#include <stdlib.h>
#include <stdio.h>

#define CMP(parent, node) (parent->self.priority > node->self.priority)

typedef struct  data {
    int priority;
    int value;
}               t_data;

typedef struct  node {
    t_data      data;
    //struct node *parent;
    //struct node *left;
    //struct node *right;
    struct node *next;
}               t_node;

typedef struct  p_queue {
    t_node      *max_p;
    t_node      *min_p;
}               t_queue;
/*
void swap(t_node *a, t_node *b)
{
    t_data d;

    d = a->self;
    a->self = b->self;
    b->self = d;
}

void heap_up(t_node *parent, t_node *node)
{
    if (!parent || !node)
        return;
    if (CMP(parent, node))
    {
        swap(parent, node);
        heap_up(parent->parent, parent);
    }
}

void heap_down(t_node *root, t_node *left, t_node *right)
{
    if (!root || !left)
        return ;
    if (!CMP(root, left))
    {
        swap(root, left);
        heap_down(left, left->left, left->right);
    }
    if (!root || !right)
        return ;
    if (!CMP(root, right))
    {
        swap(root, right);
        heap_down(right, right->left, right->right);
    }
}

int    isEmpty(t_queue *queue)
{
    return (queue->max_p == NULL || queue->min_p == NULL);
}

t_node  *init_node(t_data data)
{
    t_node  *new;

    new = (t_node *)malloc(sizeof(t_node));
    new->self = data;
    new->left = NULL;
    new->parent = NULL;
    new->right = NULL;
    printf("Value: %d Priority: %d\n", data.value, data.priority);
    return (new);
}

void tree_insert(t_queue *root, t_data data)
{
    t_node *new;

    printf("Value: %d Priority: %d\n", data.value, data.priority);
    new = init_node(data);
    if (!root->max_p)
        root->max_p = new;
    if (!root->min_p)
        root->min_p = new;
    else {
        if (!root->min_p->left)
        {
            root->min_p->left = new;
            new->parent = root->min_p;
            root->min_p = new;
        }
        if (!root->min_p->right)
        {
            root->min_p->left = new;
            new->parent = root->min_p;
            root->min_p = new;
        }
        printf("Value: %d Priority: %d\n", data.value, data.priority);
        heap_up(root->min_p, root->min_p->parent);
    }
    // create new element with data at root->min_p->left
    // set root->min_p to new element and set parent to root->min_p
    // recursive step:
    // if (!parent)
        // return
    // if (CMP  (parent, root))
        // swap (parent, root)
        // recurse
}

t_data  tree_extract(t_queue *root)
{
    t_data  data;

    data = root->max_p->self;
    root->max_p->self = root->min_p->self;
    heap_down(root->max_p, root->max_p->left, root->max_p->right);
    return (data);
    // copy root->max_p
    // change root->max_p->data to root->min_p->data
    // if (!left)
        // return
    // if (!CMP(parent, left))
        // swap(parent, left)
        // recurse
    // if (!right)
    // if (!CMP(parent, right))
        // swap(parent, right)
        // recurse
}
*/
t_data  init_data(int priority, int val)
{
    t_data  dat;

    dat.priority = priority;
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

void			enqueue(t_queue *queue, t_data num)
{
	t_node	*new;
    t_node  *tmp;

	new = (t_node *)malloc(sizeof(t_node));
	new->data = num;
	new->next = NULL;
	if (!queue->max_p)
		queue->max_p = new;
	if (!queue->min_p)
		queue->min_p = new;
	else
	{
        if (queue->min_p->data.priority > num.priority)
        {
            queue->min_p->next = new;
    		queue->min_p = queue->min_p->next;
        }
        if (queue->max_p->data.priority < num.priority)
        {
            new->next = queue->max_p;
    		queue->max_p = new;
        }
        else
        {
            tmp = queue->max_p;
            while (tmp && tmp->data.priority > num.priority)
            {
                tmp = tmp->next;
            }
            new->next = tmp->next;
            tmp->next = new;
        }
	}
}

t_data			dequeue(t_queue *queue)
{
	t_node	*tmp;
	t_data			tmp_num;

	if (!queue->max_p)
		return (init_data(0, 0));
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
		return (init_data(0, 0));
	return (queue->max_p->data);
}

int				isEmpty(t_queue *queue)
{
	return (!queue->max_p && !queue->min_p);
}

int main(void)
{
    t_data dat[8];

    dat[0] = init_data(1, 8);
    dat[1] = init_data(2, 7);
    dat[2] = init_data(3, 6);
    dat[3] = init_data(4, 5);
    dat[4] = init_data(5, 9);
    dat[5] = init_data(6, 7);
    dat[6] = init_data(7, 2);
    dat[7] = init_data(8, 1);

    t_queue *q;
    q = init();
    for (size_t i = 0; i < 8; i++) {
        enqueue(q, dat[i]);
        printf("inserting\n");
    }
    while(!isEmpty(q)){
        t_data tmp = dequeue(q);
        printf("Value: %d Priority: %d\n", tmp.value, tmp.priority);
    }
    return 0;
}
