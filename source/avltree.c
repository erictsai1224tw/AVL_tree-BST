#include "../header/avltree.h"
#include "../header/BST.h"
#include <string.h>

avl_node_t *insert(void *element, avl_node_t *node, int (*compare)(void *, void *));
avl_node_t *Delete(void *element, avl_node_t *node, int (*compare)(void *, void *));
avl_node_t *find(void *element, avl_node_t *node, int (*compare)(void *, void *));

static avl_node_t *rotateright(avl_node_t *);
static avl_node_t *rotateleft(avl_node_t *);
static avl_node_t *RR(avl_node_t *);
static avl_node_t *LL(avl_node_t *);
static avl_node_t *LR(avl_node_t *);
static avl_node_t *RL(avl_node_t *);
static int height(avl_node_t *);
static int balanceFactor(avl_node_t *);
static void update_node_height(avl_node_t *);

static void update_node_height(avl_node_t *node)
{
    if (node->left)
        update_node_height(node->left);
    if (node->right)
        update_node_height(node->right);
    node->height = height(node);
}

avl_node_t *insert(void *element, avl_node_t *root, int (*compare)(void *elementA, void *elementB))
{
    //BST insert node, note that the same value WILL NOT create the new node!!
    avl_node_t *node = (avl_node_t *)insertNode(element, (node_t *)root, compare);

    //Initial the height of node
    update_node_height(node);

    //Initial the parameter of balance factor
    int bf = balanceFactor(node);

    //for checking the element from bottom
    if ((bf > 1) || (bf < -1))
    {
        if (node->left)
            node->left = insert(NULL, node->left, compare);
        if (node->right)
            node->right = insert(NULL, node->right, compare);
    }

    //update the height of node
    update_node_height(node);

    //update the balance factor
    bf = balanceFactor(node);

    //LL
    if ((bf > 1) && (compare(element, node->left) == -1))
    {
        // printf("LL\n");
        return LL(node);
    }

    //RR
    if ((bf < -1) && (compare(element, node->right) == 1))
    {
        // printf("RR\n");
        return RR(node);
    }

    //LR
    if ((bf > 1) && (compare(element, node->left) == 1))
    {
        // printf("LR\n");
        return LR(node);
    }

    //RL
    if ((bf < -1) && (compare(element, node->right) == -1))
    {
        // printf("RL\n");
        return RL(node);
    }

    return node;
}

avl_node_t *Delete(void *element, avl_node_t *node, int (*compare)(void *, void *))
{
    //BST delete node
    if (deleteNode(element, (node_t *)node, compare) == NULL)
        return NULL;
    node->height = height(node);
    int bf = balanceFactor(node);

    if ((bf > 1) || (bf < -1))
    {
        if (node->left)
            Delete(NULL, node->left, compare);
        if (node->right)
            Delete(NULL, node->right, compare);
    }

    //LL
    if ((bf > 1) && (balanceFactor(node->left) >= 0))
        return LL(node);

    //RR
    if ((bf < -1) && (balanceFactor(node->right) <= 0))
        return RR(node);

    //LR
    if ((bf > 1) && (balanceFactor(node->left) <= 0))
    {
        return LR(node);
    }

    //RL
    if ((bf < -1) && (balanceFactor(node->right) > 0))
    {
        return RL(node);
    }

    return node;
}

avl_node_t *find(void *element, avl_node_t *node, int (*compare)(void *elementA, void *elementB))
{
    return (avl_node_t *)findNode(element, (node_t *)node, compare);
}

static avl_node_t *rotateright(avl_node_t *node)
{
    avl_node_t *temp = node->left;

    node->left = temp->right;
    temp->right = node;

    node->height = height(node);
    temp->height = height(temp);

    return temp;
}

static avl_node_t *rotateleft(avl_node_t *node)
{
    avl_node_t *temp = node->right;

    node->right = temp->left;
    temp->left = node;

    node->height = height(node);
    temp->height = height(temp);

    return temp;
}

static avl_node_t *RR(avl_node_t *node)
{
    return rotateleft(node);
}

static avl_node_t *LL(avl_node_t *node)
{
    return rotateright(node);
}

static avl_node_t *LR(avl_node_t *node)
{
    node->left = rotateleft(node->left);
    return rotateright(node);
}

static avl_node_t *RL(avl_node_t *node)
{
    node->right = rotateright(node->right);
    return rotateleft(node);
}

static int height(avl_node_t *node)
{
    int height_left = 0;
    int height_right = 0;
    if (node == NULL)
    {
        return 0;
    }
    if (node->left)
    {
        height_left = height(node->left);
    }
    if (node->right)
    {
        height_right = height(node->right);
    }

    return height_right > height_left ? ++height_right : ++height_left;
}

static int balanceFactor(avl_node_t *node)
{
    return height(node->left) - height(node->right);
}