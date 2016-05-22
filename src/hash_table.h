#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

const int HT_SIZE = 10613;

typedef struct list list;
typedef struct hash_table hash_table;

struct list
{
    char *key;
    int value;
    list *next; 
};

struct hash_table
{
    int size;
    list **chain;
    int (*hash_func)(char*); 
};


hash_table* create_table(int (*hash_func)(char*), int size)
{
    hash_table *ht = malloc(sizeof(hash_table));
    if (ht == NULL)
    {
        printf("ERROR: couldn't allocate memory");
        exit(1);
    }
    ht->size = size;
    ht->chain = malloc(sizeof(list*) * size);
    if (ht->chain == NULL)
    {
        printf("ERROR: couldn't allocate memory");
        exit(1);
    }
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

void debug_table(hash_table *ht)
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
    if (node == NULL)
    {
        printf("ERROR: couldn't allocate memory");
        exit(1);
    }
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

void ht_set(hash_table *ht, char *key, int value)
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

int ht_get(hash_table *ht, char *key)
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

int hash_func(char *s)
{
    const int P = 239; 
    long long hash = 0;
    while (*s)
    {
        hash = hash * P + *s;
        s++;
    }
    return hash % HT_SIZE;
}

#endif //HASH_TABLE_H 