#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

const int SIZE = 411;

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

list *make_node(char *key, int value)
{
    list *node = malloc(sizeof(list));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

void set(hash_table *ht, char *key, int value)
{
    long long hash = ht->hash_func(key);
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
    long long hash = ht->hash_func(key);
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
    long long hash = ht->hash_func(key);
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

void show_stats(hash_table *ht)
{
    int occup = 0, mn = SIZE, mx = -1, cnt = 0;
    double average = 0.0;
    int i;
    for (i = 0; i < ht->size; ++i)
    {
        list *node = ht->chain[i];
        if (node == NULL)
            continue; 
        occup++;
        int cur = 0;
        while (node != NULL)
        {
            cnt++;
            cur++;
            node = node->next;
        }
        mn = MIN(mn, cur);
        mx = MAX(mx, cur);
        average += cur;
    }
    average = average / (float)occup;
    printf("----statistic----\n");
    printf("min chain len: %d\n", mn);
    printf("max chain len: %d\n", mx);
    printf("total elems: %d\n", cnt);
    printf("occupied chains: %d\n", occup);
    printf("average chain: %.1f\n", average);
    printf("----statistic----\n");
}

int test_hash_func(char *s)
{
    const int P = 239; 
    long long hash = 0;
    while (*s)
    {
        hash = hash * P + *s;
        s++;
    }
    return hash % SIZE;
}

int main()
{
    hash_table *ht = create_table(test_hash_func, SIZE);

    set(ht, "1jz-ge", 200);
    set(ht, "2jz-ge", 220);
    set(ht, "1jz-gte", 280);
    set(ht, "2jz-gte", 280);
    set(ht, "3zz-fe", 110);
    debug(ht);
    del(ht, "2jz-ge");
    debug(ht);
    set(ht, "4a-ge", 125);
    debug(ht);
    printf("HoursePower of Toyota 3zz-fe engine: %d\n", get(ht, "3zz-fe"));

    show_stats(ht);
    delete_table(ht);
    return 0;
}