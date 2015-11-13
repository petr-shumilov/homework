#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} Node;


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
    Node *fast = root;
    Node *slow = root;
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

    Node *tmp3 = malloc(sizeof(Node));
    tmp3->next = root;
    tmp3->val = 3;

    Node *tmp2 = malloc(sizeof(Node));
    tmp2->next = tmp3;
    tmp2->val = 2;

    Node *tmp1 = malloc(sizeof(Node));
    tmp1->next = tmp2;
    tmp1->val = 1;

    
    root->next = tmp1;
    //root = NULL;
    
    printf("%d", find_cycle(tmp1));
    return 0;
}
