#include "../header/BST.h"
#define True 1
#define False 0

node_t *insertNode(void *element, node_t *root, int (*compare)(void *, void *));
node_t *findNode(void *element, node_t *root, int (*compare)(void *, void *));
node_t *findMinNode(node_t *root);
node_t *findMaxNode(node_t *root);
node_t *deleteNode(void *element, node_t *root, int (*compare)(void *, void *));
void inOrder(node_t *root, void (*print_)(void *)); //LVR
node_t *treeCopy(node_t *root, void *node_allo(void *));
int treeEqual(node_t *root1, node_t *root2, int *(compare)(void *, void *));

node_t *insertNode(void *element, node_t *root, int (*compare)(void *, void *))
{
    if (element==NULL)
        return root;
    
    if (root)
    {
        switch (compare(element, root))
        {
        case 1: //element(data) > node->data
            if (root->right == NULL) //把element插入(串)在空的位置
            {
                root->right = element;
                node_t *temp = root->right;
                temp->left = NULL;
                temp->right = NULL;
            }
            else
            {
                insertNode(element, root->right, compare); //不是空的，繼續比較
            }
            break;
        case -1: //element(data) < node->data
            if (root->left == NULL) //把element插入(串)在空的位置
            {
                root->left = element;
                node_t *temp = root->left;
                temp->left = NULL;
                temp->right = NULL;
            }
            else
            {
                insertNode(element, root->left, compare); //不是空的，繼續比較
            }
            break;
        case 0: //equal, no need to insert
            break;
        }
    }
    else
    {
        root = element;
        root->right = NULL;
        root->left = NULL;
    }
    return root;
}

node_t *findNode(void *element, node_t *root, int (*compare)(void *, void *))
{
    if (root)
    {
        switch (compare(element, root))
        {
        case 1: //element data > root data
            return findNode(element, root->right, compare);
        case -1: //element data < root data
            return findNode(element, root->left, compare);
        case 0: //equal
            return root;
        default:
            return NULL;
        }
    }
    else
        return NULL; //no found
}

node_t *findMinNode(node_t *root)
{
    node_t *temp = root;
    if (temp->left == NULL)
        return temp;
    return findMinNode(temp->left);
}

node_t *findMaxNode(node_t *root)
{
    node_t *temp = root;
    if (temp->right == NULL)
        return temp;
    return findMaxNode(temp->right);
}

node_t *deleteNode(void *element, node_t *root, int (*compare)(void *, void *))
{
    if (element == NULL)
        return root;
    node_t *temp;
    if (root == NULL)
        printf("element didn't exist\n");
    else
    {
        if (compare(element, root) == 1) //element>node
        {
            root->right = deleteNode(element, root->right, compare);
        }
        else if (compare(element, root) == -1) //element<node
        {
            root->left = deleteNode(element, root->left, compare);
        }
        else //element=node
        {
            if ((root->left) && (root->right))
            {
                temp = findMinNode(root->right); //catch the min. num in right subtree
                root = temp;
                root->right = deleteNode(temp, root->right, compare); //delete the min. num in right subtree
            }
            else if (root->left == NULL)
            {
                //temp = root;
                root = root->right;
                //free(temp);
            }
            else
            {
                //temp = root;
                root = root->left;
                //free(temp);
            }
        }
    }
    return root;
}

void inOrder(node_t* root, void (*print_)(void *)) //LVR
//user DIY the print function(depent on which data that he want to print)
{
    if (root)
    {
        inOrder(root->left, print_);
        print_(root);
        inOrder(root->right, print_);
    }
}

void preOrder(node_t *root, void (*print_)(void *)) //VLR
{
    if (root)
    {
        print_(root);
        preOrder(root->left, print_);
        preOrder(root->right, print_);
    }
}

void postOrder(node_t *root, void (*print_)(void *)) //LRV
{
    if (root)
    {
        postOrder(root->left, print_);
        postOrder(root->right, print_);
        print_(root);
    }
}

node_t *treeCopy(node_t *root, void *node_allo(void *)) //VLR pre-order
//user DIY copy his element's content,
//input:old tree's root, and return the site of new node
{
    if (root == NULL)
    {
        return NULL;
    }

    node_t *new_node = (node_t *)node_allo(root);

    if ((root->left == NULL) && (root->right == NULL))
    {
        return new_node;
    }
    new_node->left = treeCopy(root->left, node_allo);
    new_node->right = treeCopy(root->right, node_allo);
    return new_node; //return new tree's root
}

int treeEqual(node_t *root1, node_t *root2, int *(compare)(void *, void *))
//USER needs to DIY 'compare'
//only needs to return 1(true) or 0(false)
{
    if ((root1 == NULL) && (root2 == NULL))
        return True;
    else if ((root1 != NULL) && (root2 == NULL))
        return False;
    else if ((root1 == NULL) && (root2 != NULL))
        return False;
    else if (compare(root1, root2) == False) //compare data
        return False;
    else
    {
        if ((treeEqual(root1->left, root2->left, compare) == True) &&
            ((treeEqual(root1->right, root2->right, compare) == True)))
            return True;
        else
            return False;
    }
}