#include "../header/avltree.h"
#include <stdio.h>
#include <string.h>

typedef struct myElement
{
    avl_node_t node;
    char ID[11];
    int math;
    int eng;
} student_t;

student_t *root = NULL;

int compareMath(void *elementA, void *elementB)
{
    int mathA = ((student_t *)elementA)->math;
    int mathB = ((student_t *)elementB)->math;
    if (mathA > mathB)
    {
        return 1;
    }
    if (mathA < mathB)
    {
        return -1;
    }
    else
        return 0;
}

void print(void *element)
{
    student_t *temp = (student_t *)element;
    printf("id=%s, math=%d, english=%d\n", temp->ID, temp->math, temp->eng);
}

void PRINT_in_pre_postOrder(void *root, void print(void *element))
{
    printf("\ninOrder:\n");
    inOrder((node_t *)root, print);
    printf("\n\n---------------\n\n");
    printf("preOrder:\n");
    preOrder((node_t *)root, print);
    printf("\n\n---------------\n\n");
    printf("postOrder:\n");
    postOrder((node_t *)root, print);
}

int main()
{

    student_t node0, node1, node2, node3, node4, node5;

    strcpy(node0.ID, "C120308001");
    node0.math = 40;
    node0.eng = 100;

    strcpy(node1.ID, "B220406001");
    node1.math = 20;
    node1.eng = 90;

    strcpy(node2.ID, "D120306001");
    node2.math = 60;
    node2.eng = 95;

    strcpy(node3.ID, "A220407001");
    node3.math = 10;
    node3.eng = 90;

    strcpy(node4.ID, "D220506001");
    node4.math = 30;
    node4.eng = 70;

    strcpy(node5.ID, "A120406001");
    node5.math = 25;
    node5.eng = 90;

    root = (student_t *)insertNode((void *)&node0, (node_t *)root, compareMath);
    root = (student_t *)insertNode((void *)&node1, (node_t *)root, compareMath);
    root = (student_t *)insertNode((void *)&node2, (node_t *)root, compareMath);
    root = (student_t *)insertNode((void *)&node3, (node_t *)root, compareMath);
    root = (student_t *)insertNode((void *)&node4, (node_t *)root, compareMath);
    root = (student_t *)insertNode((void *)&node5, (node_t *)root, compareMath);
    printf("Binary Search Tree:\n");
    PRINT_in_pre_postOrder(root, print);

    root = NULL;
    root = (student_t *)insert((void *)&node0, (avl_node_t *)root, compareMath);
    root = (student_t *)insert((void *)&node1, (avl_node_t *)root, compareMath);
    root = (student_t *)insert((void *)&node2, (avl_node_t *)root, compareMath);
    root = (student_t *)insert((void *)&node3, (avl_node_t *)root, compareMath);
    root = (student_t *)insert((void *)&node4, (avl_node_t *)root, compareMath);
    root = (student_t *)insert((void *)&node5, (avl_node_t *)root, compareMath);
    printf("----------\nAVL Tree:\n");
    PRINT_in_pre_postOrder(root, print);

    Delete((void *)&node3, (avl_node_t *)root, compareMath);
    printf("----------\nAVL Tree delete node3:\n");
    PRINT_in_pre_postOrder(root, print);

    printf("\n----------------\n");
    printf("node2 site in tree:%x\n",(int)find((void *)&node2, (avl_node_t *)root, compareMath));
    printf("node2 real site:%x\n",(int)&node2);

    return 0;
}