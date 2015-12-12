#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node
{
    int val;
    Node *next;
};

void print(Node *root, int cnt)
{
    if (!root)
        return;
    printf("%d ", root->val);
    if (cnt <= 10)
        cnt++, print(root->next, cnt);
}

int find_cycle(Node *root)
{
    Node *fast, *slow;
    fast = slow = root;
    int delay = 0;
    while (1)
    {
        if (!fast)
            return 0;
        if (delay)
            slow = slow->next;
        delay = !delay;
        fast = fast->next;
        if (fast == slow)
            return 1;
    }
}

int main()
{
    Node *root = malloc(sizeof(Node));
    Node *node1 = malloc(sizeof(Node));
    Node *node2 = malloc(sizeof(Node));
    Node *node3 = malloc(sizeof(Node));

    root->next = node1;

    node1->val = 1;
    node1->next = node2;

    node2->val = 2;
    node2->next = node3;
    
    node3->val = 3;

    
    node3->next = node2;
    //if you want have cycle, comment out next line
    //node3->next = NULL;
    
    
    print(root, 0);
    printf("\nHave cycle: %d", find_cycle(root));
    return 0;
}
