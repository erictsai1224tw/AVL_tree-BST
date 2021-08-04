#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left;
    struct node *right;
} node_t;

node_t *insertNode(void *element, node_t *root, int (*compare)(void *, void *));
node_t *findNode(void *element, node_t *root, int (*compare)(void *, void *));
node_t *findMinNode(node_t *root);
node_t *findMaxNode(node_t *root);
node_t *deleteNode(void *element, node_t *root, int (*compare)(void *, void *));
void inOrder(node_t *root, void (*print_)(void *));   //LVR
void preOrder(node_t *root, void (*print_)(void *));  //VLR
void postOrder(node_t *root, void (*print_)(void *)); //LRV
node_t *treeCopy(node_t *root, void *node_allo(void *));
int treeEqual(node_t *root1, node_t *root2, int *(compare)(void *, void *));

#endif // BST_H_INCLUDED