#ifndef __AVLTREE_H__
#define __AVLTREE_H__
#include "BST.h"
typedef struct avl_node
{
    struct avl_node *left;
    struct avl_node *right;
    int height;
} avl_node_t;

avl_node_t *insert(void *element, avl_node_t *root, int (*compare)(void *, void *));
avl_node_t *Delete(void *element, avl_node_t *root, int (*compare)(void *, void *));
avl_node_t *find(void *element, avl_node_t *root, int (*compare)(void *, void *));

static avl_node_t *rotateright(avl_node_t *);
static avl_node_t *rotateleft(avl_node_t *);
static avl_node_t *RR(avl_node_t *);
static avl_node_t *LL(avl_node_t *);
static avl_node_t *LR(avl_node_t *);
static avl_node_t *RL(avl_node_t *);
static int height(avl_node_t *);
static int balanceFactor(avl_node_t *);
#endif