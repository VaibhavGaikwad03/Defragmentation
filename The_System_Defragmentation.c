#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 10

// data blocks structure
struct node
{
    struct node *prev;
    int data;
    struct node *next;
};

// to check disk blocks are full or not
int is_full(struct node *head, struct node *tail)
{
    if (head == NULL)
        return -1;

    do
    {
        if (head->data == 0)
            return 0;
        head = head->next;
    } while (head != tail->next);
    return 1;
}

// to check disk blocks are empty or not
int is_empty(struct node *head, struct node *tail)
{
    if (head == NULL)
        return -1;

    do
    {
        if (head->data != 0)
            return 0;
        head = head->next;
    } while (head != tail->next);
    return 1;
}

// to display disk blocks arrangement
void display(struct node *head, struct node *tail)
{
    if (head == NULL)
    {
        printf("\nList is empty.\n");
        return;
    }

    printf("\nData blocks arrangement is:\n");

    do
    {
        printf("[%d]<->", head->data);
        head = head->next;
    } while (head != tail->next);
    printf("\n");
}

// to write data into existing list
void insert_data(struct node **ptr, int data)
{
    while ((*ptr)->data != 0)
        *ptr = (*ptr)->next;
    (*ptr)->data = data;
}

// to delete data from blocks
int delete_data(struct node *head, int pos)
{
    int counter;
    struct node *temp = head;

    if (pos < 1 || pos > MAX_NODES)
        return -2;

    for (counter = 1; counter < pos; counter++)
        temp = temp->next;

    if (temp->data == 0)
        return -1; // data already deleted

    temp->data = 0; // deleting data

    return 0; // data successfully deleted
}

// to create list of data blocks
struct node *create_list(struct node **head, struct node **tail)
{
    int counter;
    struct node *new_node = NULL;

    for (counter = 1; counter <= MAX_NODES; counter++)
    {
        new_node = (struct node *)malloc(sizeof(struct node));

        if (new_node == NULL)
        {
            printf("\nMemory allocation FAILED.\n");
            exit(1); // failure
        }

        new_node->data = 0;

        if (*head == NULL)
            *head = *tail = new_node;
        else
        {
            new_node->prev = *tail;
            (*tail)->next = new_node;
            *tail = new_node;
        }
        (*head)->prev = *tail;
        (*tail)->next = *head;
    }
    return (*head);
}

// to free all memory
void delete_all(struct node **head, struct node **tail)
{
    struct node *temp = NULL;

    if (*head == NULL)
        return;

    temp = *head;
    (*tail)->next = NULL;

    while (temp != NULL)
    {
        *head = temp->next;
        temp->next = NULL;
        free(temp);
        temp = *head;
    }
}

// to defragment data blocks
void defragment(struct node *head, struct node *tail, struct node **ptr)
{
    int displacement;
    struct node *temp = NULL;

    if (is_full(head, tail))
        return;

    while (1)
    {
        temp = head;
        displacement = 0;

        while (temp != tail)
        {
            if (temp->data != 0 && temp->next->data == 0)
            {
                temp->next->data = temp->data;
                temp->data = 0;
                displacement++;
            }
            temp = temp->next;
        }
        if (displacement == 0)
            break;
    }
    *ptr = head;
}

int main(void)
{
    int ret;
    int pos;
    int value;
    int choice;
    struct node *ptr = NULL;
    struct node *first = NULL;
    struct node *last = NULL;

    ptr = create_list(&first, &last);

    while (1)
    {
        printf("\nEnter your choice: ");
        printf("\n1. Insert\n2. Delete\n3. Defragment\n4. Exit\n>_");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (!is_full(first, last))
            {
                printf("\nEnter the data: ");
                scanf("%d", &value);
                insert_data(&ptr, value);
                display(first, last);
            }
            else    
                printf("\nList is full.\n");
            break;

        case 2:
            if (!is_empty(first, last))
            {
                printf("\nEnter the position: ");
                scanf("%d", &pos);

                ret = delete_data(first, pos);

                if (ret == 0)
                    printf("\nData deleted successfully.\n");
                else if(ret == -1)
                    printf("\nData already deleted.\n");
                else    
                    printf("\nInvalid position.\n");

                display(first, last);
            }
            else
                printf("\nList is empty.\n");
            break;

        case 3:
            defragment(first, last, &ptr);
            display(first, last);
            break;

        case 4:
            delete_all(&first, &last);
            exit(0);
            break;

        default:
            printf("\nInvalid choice.\n");
        }
    }
    return 0;
}
