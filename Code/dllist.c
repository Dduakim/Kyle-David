#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *nextptr;
    struct node *prevptr;
}
*firstNode, *lastNode;

void createNodeList(int n);
void displayNodeList(int n);

int main (void)
{
    int n;
    printf("This is a program to make a doubly-linked list\nHow many nodes would you like?: ");
    scanf("%i", &n);
    createNodeList(n);
    printf("This is the data you inputted:\n");
    displayNodeList(n);
    return 0;
}

void createNodeList(int n)
{
    struct node *tempNode;
    int nodeNum, i;
    firstNode = (struct node *)malloc(sizeof(struct node));

    if (firstNode == NULL)
    {
        printf("Memory cannot be allocated\n");
    }
    else
    {
        printf("Input data for node 1: ");
        scanf("%i", &nodeNum);
        firstNode -> value = nodeNum;
        firstNode -> nextptr = NULL;
        firstNode -> prevptr = NULL;
        tempNode = firstNode;

        for (i = 2; i <= n; i++)
        {
          lastNode = (struct node *)malloc(sizeof(struct node));
          if (lastNode == NULL)
          {
            printf("Memory cannot be allocated");
            break;
          }
          else
          {
            printf("Input data for node %i: ", i);
            scanf("%i", &nodeNum);

            lastNode -> value = nodeNum;
            lastNode -> nextptr = NULL;
            lastNode -> prevptr = tempNode;

            tempNode -> nextptr = lastNode;
            tempNode = tempNode -> nextptr;
          }
        }
    }
}

void displayNodeList(int n)
{
    struct node *tempNode;
    if (firstNode  == NULL) // if no value in the first node then theres no List
    {
        printf("List is empty\n");
    }
    else
    {
        tempNode = firstNode;
        for (int i = 0; i < n; i++)
        {
            printf("Data = %i\n", tempNode -> value); // printing the number value held at temp node
            tempNode = tempNode -> nextptr; // moving temp pointer along
        }
        printf("And backwards!\n");
        tempNode = lastNode;
        for (int i = n; i > 0; i--)
        {
            printf("Data = %i\n", tempNode -> value); // printing the number value held at temp node
            tempNode = tempNode -> prevptr; // moving temp pointer along
        }
    }
}
