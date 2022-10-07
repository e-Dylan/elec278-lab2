// stackproblem.c - Lab 02 - Dylan, Smith

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    false = 0,
    true
} bool,
    *pbool;

// Definition of stack node - this version implements stack of integers
typedef struct node
{
    struct node *next;
    int nodval;
} Node;

#define SIZENODE (sizeof(struct node))

// This implementation has only one stack
Node *head = NULL;

int push(int n)
// Top of stack is front of linked list.  Create node to hold data and
// place it at front of list. Returns 0 if no node created; 1 for success.
{
    Node *p = (Node *)malloc(SIZENODE);
    if (p == NULL)
        return 0;
    p->nodval = n;
    p->next = head;
    head = p;
    return 1;
} // push()

int pop(int *pvalue)
// Top of stack is front of linked list. Check if list empty; if not,
// remove first node on list and copy value to supplied location.
{
    int rslt = 0;
    if (pvalue != NULL)
    {
        Node *p = head;
        if (p != NULL)
        {
            head = p->next;
            *pvalue = p->nodval;
            free(p);
            rslt = 1;
        } // endif stack not empty
    }     // endif result location available
    return rslt;
} // pop()

int main()
{
    FILE *fp;
    char file_name[] = "stackproblem.txt";
    char ch;
    int result;
    int value;

    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        // failed to open file - report the problem
        fprintf(stderr, "ERROR: Cannot open %s\n", file_name);
        return -1;
    }

    // Traverse the text and add each character to the stack
    while (ch != EOF && ch != '\n')
    {
        ch = getc(fp);
        if (ch == EOF || ch == '\n')
        {
            break;
        }
        push(ch - '0');
    }
    // Traverse the stack and print out each data value.
    while (result = pop(&value))
        printf("%d", value);
}