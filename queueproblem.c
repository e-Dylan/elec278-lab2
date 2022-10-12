// queueproblem.c - Lab 02 - Dylan, Smith

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

typedef struct queue
{
    struct node *front, *end;
} Queue;

Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

Queue *createEmptyQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->end = NULL;
    return q;
}

void addToEnd(Queue *q, int value)
{
    Node *newNode = createNode(value);

    // if queue is empty, new node is front and back
    if (q->front == NULL)
    {
        q->front = newNode;
        q->end = newNode;
        return;
    }

    // add new node to back of the queue, update end
    q->end->next = newNode;
    q->end = newNode;
}

Node *removeFromFront(Queue *q)
{
    // queue is empty, do nothing
    if (q->front == NULL)
        return NULL;

    Node *removedNode = q->front;

    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->end = NULL;
    }

    return removedNode;
}

void printList(Node *head)
{
    Node *temp; // temporary pointer used to traverse list
    int count;  // count how many printed on one line
    if (head == NULL)
    {
        printf("<EMPTY LIST>\n");
        return;
    }
    // List has some real data to be printed. We will point temp at
    // the first node in the list, print the data, and if there is
    // more list, move temp to point to the next node. We'll keep
    // doing this until there are no more nodes to look at.
    temp = head;
    count = 0; // 0 on line so far
    while (temp != NULL)
    {
        printf("%5d", temp->value);
        if (temp->next != NULL)
        {
            count++; // one more on the line
            // check if getting close to right edge - if so, move to start of
            // next line and reset count.
            if (count >= 12)
            {
                putchar('\n');
                count = 0;
            }
        }
        else
        {
            putchar('\n');
        }
        temp = temp->next;
    }
    return;
}

// Merge two linked lists together.
void *merge(Node *front1, Node *front2)
{
    if (front1 == NULL)
        return NULL;
    Node *temp1 = front1;
    // traverse to end of first list
    while (temp1->next != NULL)
    {
        temp1 = temp1->next;
    }
    temp1->next = front2;
}

int main()
{
    Queue *q1 = createEmptyQueue();
    Queue *q2 = createEmptyQueue();
    Queue *q3 = createEmptyQueue();
    Queue *q4 = createEmptyQueue();

    FILE *fp;
    char fileName[] = "queueproblem.txt";
    int num = 0;

    // Open the input file
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        // failed to open file - report the problem
        fprintf(stderr, "ERROR: Cannot open %s\n", fileName);
        return -1;
    }

    fscanf(fp, "%d", &num);
    while (!feof(fp))
    {
        if (num < 0)
        {
            // Merge all the queue's linked lists in order.
            merge(q1->front, q2->front);
            merge(q1->front, q3->front);
            merge(q1->front, q4->front);

            // Print the final linked list, which is all the queue's linked in order.
            printList(q1->front);
            break;
        }

        if (num % 4 == 0)
        {
            addToEnd(q1, num);
        }
        else if (num % 4 == 1)
        {
            addToEnd(q2, num);
        }
        else if (num % 4 == 2)
        {
            addToEnd(q3, num);
        }
        else if (num % 4 == 3)
        {
            addToEnd(q4, num);
        }

        fscanf(fp, "%d", &num);
    }

    // Reached end of file without a negative integer.
}