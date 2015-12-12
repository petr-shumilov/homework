#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node
{
    int val;
    Node *next;
};

void add(Node **root, Node **last, int val)
{
    Node *new = malloc(sizeof(Node)); 
    new->val = val;
    new->next = NULL;
    (*last)->next = new;
    *last = new; 
}

void rm(Node *root, Node **last, int val)
{
    Node *prev = root, *cur = root->next;
    while (cur && cur->val != val)
    {
        prev = cur;
        cur = cur->next;
    }
    if (cur && cur->val == val)
    {
        if (cur == *last)
            *last = prev;
        prev->next = cur->next;
    }
}

void print(Node *root)
{
    Node *item = root->next;
    if (item == NULL)
        printf("NULL\n");
    else
    {
        while (item)
        {
            printf("%d->", item->val);
            item = item->next;
        }
        printf("NULL\n");
     }       
}

void free_mem(Node *root)
{
    if (!root)
        return;
    free_mem(root->next);
    free(root);
}

void quit(Node *root)
{
    free_mem(root);
    exit(0);
    return;
}

int main()
{
    Node *root = malloc(sizeof(Node)), *last = malloc(sizeof(Node));
    last = root;
    while(1)
    {
        char command;
        int tmp;
        scanf("%c", &command);
        switch (command)
        {
            case 'a':
                scanf("%d", &tmp);
                add(&root, &last, tmp);
            break;
            case 'r':
                scanf("%d", &tmp);
                rm(root, &last, tmp);
            break;
            case 'p':
                print(root);
                printf("\n");
            break;
            case 'q':
                quit(root);
            break;
        }
    }
    return 0;
}
