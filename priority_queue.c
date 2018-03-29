#include <stdlib.h>

typedef struct  data {
    int wait_cycle;
    int value;
}               t_data;

typedef struct  node {
    t_data      self;
    struct node *left;
    struct node *right;
}               t_node;

void tree_insert(t_node *root, t_data data)
{
    /* code */
}

void swap(t_node *a, t_node *b)
{
    t_data d;

    d = a->self;
    a->self = b->self;
    b->self = d;
}

t_data  tree_extract(t_node *root)
{
    t_data  tmp;

    tmp = root->self;
    if
    return (tmp);
}
