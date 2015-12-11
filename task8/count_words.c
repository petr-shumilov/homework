#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

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

int hash1(char *s)
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

int hash2(char *s)
{
    return 239;
}

int hash3(char *s)
{
    int i, hash = 0;
    for (i = 0; i < strlen(s); i++)
        hash += s[i];
    return hash % SIZE;
}


int main()
{
    FILE *in = fopen("input.txt", "r");
    freopen("statistic.txt", "w", stdout);
    printf("SIZE OF HASHTABLE: %d\n", SIZE);
    char s[256];
    
    time_t start = clock();
    hash_table *ht1 = create_table(hash1, SIZE);
    while (fscanf(in, "%s", s) == 1)
    {
        if (get(ht1, s) == -1)
            set(ht1, s, 0);
        else
        {
            int tmp = get(ht1, s);
            set(ht1, s, tmp++);
        }
    }
    printf("Time of stable hash: %f sec.\n", (clock() - start) / (double)CLOCKS_PER_SEC);
    show_stats(ht1);
    delete_table(ht1);
    printf("\n\n");
    
    start = clock();
    hash_table *ht2 = create_table(hash2, SIZE);
    fseek(in, 0, SEEK_SET);
    while (fscanf(in, "%s", s) == 1)
    {
        if (get(ht2, s) == -1)
            set(ht2, s, 0);
        else
        {
            int tmp = get(ht2, s);
            set(ht2, s, tmp++);
        }
    }
    printf("Time of hash when using constant: %f sec.\n", (clock() - start) / (double)CLOCKS_PER_SEC);
    show_stats(ht2);
    delete_table(ht2);
    printf("\n\n");
    
    start = clock();
    hash_table *ht3 = create_table(hash3, SIZE);
    fseek(in, 0, SEEK_SET);
    while (fscanf(in, "%s", s) == 1)
    {
        if (get(ht3, s) == -1)
            set(ht3, s, 0);
        else
        {
            int tmp = get(ht3, s);
            set(ht3, s, tmp++);
        }
    }
    printf("Time of hashing by sums: %f sec.\n", (clock() - start) / (double)CLOCKS_PER_SEC);
    show_stats(ht3);
    delete_table(ht3);
    return 0;
}