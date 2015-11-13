#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} Node;

void add(Node **root, int val)
{
    Node *tmp = malloc(sizeof(Node));
    tmp->val = val;
    tmp->next = *root;
    *root = tmp;
}

void print(Node *root)
{
    if (!root)
        return;
    printf("%d ", root->val);
    print(root->next);
}


Node* get_Nth(Node *root, int n)
{
    int cnt = 0;
    while (cnt < n && root)
    {
        root = root->next;
        cnt++;
    }
    return root;
}

int find(Node *root, int val)
{
    int pos = 0;
    while (root->val != val && root)
    {
        root = root->next;
        pos++;
    }
    return pos;
}

void rm(Node *root, int val)
{
    int n = find(root, val);
    if (!n)
        return;
    Node *tmp = get_Nth(root, n - 1);
    Node *tmp2 = tmp->next;
    tmp->next = tmp2->next;
}

void free_mem(Node *root)
{
    if (!root)
        return;
    free(root);
    free_mem(root->next);
}

void quit(Node *root)
{
    free_mem(root);
    exit(0);
    return;
}

int main()
{
    Node *root = NULL;
    while(1)
    {
        char command;
        int tmp;
        scanf("%c", &command);
        switch (command)
        {
            case 'a':
                scanf("%d", &tmp);
                add(&root, tmp);
            break;
            case 'r':
                scanf("%d", &tmp);
                rm(root, tmp);
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
