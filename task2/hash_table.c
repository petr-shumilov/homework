#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 10613;

typedef struct list
{
    char *key;
    int value;
    struct list *next; 
} list;

typedef struct hash_table
{
    int size;
    list **chain;
    int (*hash_func)(char*); 
} hash_table;


hash_table* create_table(int (*hash_func)(char*), int size)
{
    hash_table *ht = malloc(sizeof(hash_table));
    ht->size = size;
    ht->chain = malloc(sizeof(list*) * size);
    ht->hash_func = hash_func;
    int i;
    for (i = 0; i < size; ++i)
        ht->chain[i] = NULL;
    return ht;
}

void delete_table(hash_table *ht)
{
    int i;
    for (i = 0; i < ht->size; ++i)
    {
        list *node = ht->chain[i], *tmp;
        while (node != NULL)
        {
            tmp = node->next;
            free(node);
            node = tmp;
        }
        free(node);
    }
    free(ht->chain);
    free(ht);
}

void debug(hash_table *ht)
{
    printf("---DEBUG---\n");
    int i;
    for (i = 0; i < ht->size; ++i)
    {
        list *item = ht->chain[i];
        if (item == NULL)
            continue;
        printf("%d: ", i);
        while (item != NULL)
        {
            printf("['%s', %d]->", item->key, item->value);
            item = item->next;
        }
        printf("NULL\n");
    }
    printf("---DEBUG---\n");
}

void print(hash_table *ht)
{
    int i;
    for (i = 0; i < ht->size; ++i)
    {
        list *item = ht->chain[i];
        if (item == NULL)
            continue;
        while (item != NULL)
        {
            printf("['%s'] = %d\n", item->key, item->value);
            item = item->next;
        }
    }
}

list *make_node(char *key, int value)
{
    list *node = malloc(sizeof(list));
    node->key = strdup(key); //real sh*t
    node->value = value;
    node->next = NULL;
    return node;
}

void set(hash_table *ht, char *key, int value)
{
    int hash = ht->hash_func(key);
    list *node = ht->chain[hash], *last = NULL;
    while (node != NULL)
    {
        last = node;
        if (strcmp(key, node->key) == 0)
        {
            node->value = value;
            return;
        }
        else
            node = node->next;
    }
    if (last == NULL)
        ht->chain[hash] = make_node(key, value);
    else
        last->next = make_node(key, value);
}

int get(hash_table *ht, char *key)
{
    int hash = ht->hash_func(key);
    list *node = ht->chain[hash];

    while (node != NULL)
    {
        if (strcmp(key, node->key) == 0)
            return node->value;
        node = node->next;
    }
    return -1; 
}

void del(hash_table *ht, char *key)
{
    int hash = ht->hash_func(key);
    list *node = ht->chain[hash], *last = NULL;

    while (node != NULL)
    {
        if (strcmp(key, node->key) == 0)
        {
            if (last == NULL)
                ht->chain[hash] = node->next;
            else
                last->next = node->next;
            free(node);
            return;
        }
        last = node;
        node = node->next;
    }
}

int hash(char *s)
{
    const int P = 239; 
    long long hash = 0;
    while (*s)
    {
        hash =(hash * P + *s) % SIZE;
        s++;
    }
    return hash % SIZE;
}

int main()
{
    hash_table *ht = create_table(hash, SIZE);
    while (1)
    {
        char cur[255];
        scanf("%s", cur);
        if (!strcmp(cur, "exit"))
            break;
        int pos = get(ht, cur);
        if (pos == -1)
            set(ht, cur, 1);
        else
            set(ht, cur, pos + 1);
    }
    print(ht);
    return 0;
}

