#include <stdio.h>
#include <stdlib.h>

struct node
{
    int num;
    struct node *next;
}
*startNode;

void createNodeList(int n); // take an input of n and makes a list with n amount of nodes
void displayList(); // function to display the list

int main ()
{
    int n;
    printf("How large would you like your list to be: \n");
    scanf("%i", &n);
    createNodeList(n);
    printf("Input your data for the list: \n");
    displayList();
    return 0;
}

void createNodeList(int n)
{
    struct node *lastNode, *temp; // just declaring structs & variables
    int num, i;
    startNode = (struct node *)malloc(sizeof(struct node)); // dynamically allocating memory the size of a node and storing it at pointer to startNode

    if (startNode == NULL) // just in case memory cannot be allocated, in which case it would point to NULL
    {
        printf("Memory cannot be allocated \n");
    }
    else
    {
        printf("Input data for node 1: ");
        scanf("%i", &num); // receive input from user, store at address to int num
        startNode -> num = num; // make it so that the value stored at startNode is now equal to the num we received from user
        startNode -> next = NULL; // make the pointer that startNode points to equal NULL; this is now the last link
        temp = startNode; // setting our temporary node as equal to our startNode

        for (i = 2; i <= n; i++) // iterating through until hits number of n (size of linked list); starts at 2 to prevent issues with linked list of size 1
        {
            lastNode = (struct node *)malloc(sizeof(struct node)); // allocating memory for new node
            if (lastNode == NULL) // same as before, if memory cannot be allocated, break
            {
                printf("Memory cannot be allocated \n");
                break;
            }
            else
            {
                printf("Input data for node %i: ", i); // receive input from user for next node number value held
                scanf("%i", &num);

                lastNode -> num = num; // assign value in node to number received
                lastNode -> next = NULL; // set the pointer value in lastNode to NULL

                temp -> next = lastNode; // make pointer in temp node now point to lastNode
                temp = temp -> next; // not sure about this one...

            }
        }
    }
}

void displayList()
{
    struct node *temp;
    if (startNode  == NULL) // if no value in the first node then theres no List
    {
        printf("List is empty\n");
    }
    else
    {
        temp = startNode;
        while (temp != NULL) // basically recursive, it continues printing until it reaches the start node which has value NULL
        {
            printf("Data = %i\n", temp -> num); // printing the number value held at temp node
            temp = temp -> next; // moving temp pointer along?
        }
    }
}
