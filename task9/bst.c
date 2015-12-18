#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <assert.h>

typedef struct Node Node;
typedef enum {PREORDER, INCORDER, DECORDER} PRINT_TYPE;

struct Node
{
    int value;
    Node *left, *right;
};

Node *get_min(Node *Tree)
{
    if (Tree->left != NULL)
        return get_min(Tree->left);
    return Tree;
}

void insert(Node **Tree, int value)
{
    if (*Tree == NULL)
    {
        Node *tmp = (Node*)malloc(sizeof(Node));
        if (tmp == NULL)
        {
            printf("ERROR: couldn't allocate memory");
            exit(1);
        }
        tmp->value = value;
        tmp->left = tmp->right = NULL;
        *Tree = tmp;
    } 
    if (value < (*Tree)->value)
        insert(&(*Tree)->left, value);
    else if ((*Tree)->value < value)
        insert(&(*Tree)->right, value);
}


void erase(Node **Tree, int value)
{
    if (*Tree == NULL)
        return;
    if (value < (*Tree)->value)
        erase(&(*Tree)->left, value);
    else if ((*Tree)->value < value)
        erase(&(*Tree)->right, value);
    else
    {
        if ((*Tree)->left && (*Tree)->right)
        {
            Node *next = get_min((*Tree)->right);
            (*Tree)->value = next->value;
            erase(&(*Tree)->right, next->value);
            return;
        }
        else if ((*Tree)->right)
        {
            erase(&(*Tree)->right, value);
            free(*Tree);
            return;
        }
        else if ((*Tree)->left)
        {
            erase(&(*Tree)->left, value);
            free(*Tree);
            return;
        }
        else
        {
            *Tree = NULL;
            free(*Tree);
            return;
        }
    }
}

int exist(Node *Tree, int value)
{
    if (Tree == NULL)
        return 0;   
    if (value < Tree->value)
        return exist(Tree->left, value);
    else if (Tree->value < value)
        return exist(Tree->right, value);
    else
        return 1;
}


void print(Node *Tree, PRINT_TYPE type)
{
    switch(type)
    {
        case PREORDER:
            if (Tree == NULL)
            {
                printf("NULL ");
                return;
            }
            printf("(%d ", Tree->value);
            print(Tree->left, PREORDER);
            print(Tree->right, PREORDER);
            printf(")");
            break;
        case INCORDER:
            if (Tree != NULL)
            {
                print(Tree->left, INCORDER);
                printf("%d ", Tree->value);
                print(Tree->right, INCORDER);
            }
            break;
        case DECORDER:
            if (Tree != NULL)
            {
                print(Tree->right, DECORDER);
                printf("%d ", Tree->value);
                print(Tree->left, DECORDER);
            }
            break;
    }
}

int main()
{
    Node *root = (Node*)malloc(sizeof(Node));
    if (root == NULL)
    {
        printf("ERROR: couldn't allocate memory");
        exit(1);
    }
    
    root->value = LONG_MAX;
    root->left = root->right = NULL;
    
    insert(&root, 2);
    insert(&root, 1);
    insert(&root, 4);
    insert(&root, 3);
    insert(&root, 5);

    print(root->left, PREORDER);
    printf("\n");
    
    printf("exitst(4): %d\n", exist(root, 4));
    
    erase(&root, 4);
    print(root->left, PREORDER);
    printf("\n");
    
    printf("exitst(4): %d\n", exist(root, 4));

    erase(&root, 1);
    print(root->left, PREORDER);
    printf("\n");
    print(root->left, INCORDER);
    printf("\n");
    print(root->left, DECORDER);
    printf("\n");

    return 0;
}