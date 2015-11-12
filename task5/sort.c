#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int N[9] = {5, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
const int MOD = 100000;

inline void print(int *arr, int _size)
{
    int i;
    for (i = 0; i < _size; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void sort0(int *arr, int _size) // ~O(n)
{
    int *count = (int*)malloc((MOD + 0) * sizeof(int));

    int i, j = 0;
    for (i = 0; i < _size; ++i)
        count[arr[i]]++;

    for (i = 0; i < MOD; ++i)
        if (count[i])
            for (j = 0; j < count[i]; ++j)
            {
                //printf("%d ", i);
            }

    free(count);
}

void sort1(int* arr, int l, int r, int _size)  //O(n log n)
{
    int i = l,
    j = r,
    m = arr[(l + r) / 2];

    do
    {
        while (arr[i] < m)
            i++;
        while (arr[j] > m)
            j--;
        if (i <= j)
        {
            if (arr[i] > arr[j])
            {
                int swp = arr[i];
                arr[i] = arr[j];
                arr[j] = swp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < r)
        sort1(arr, i, r, _size);
    if (l < j)
        sort1(arr, l, j, _size);

    //if (l == 0 && r == _size)
    //    print(arr, _size);
}

void sort2(int *arr, int _size) //O(n ^ 2)
{
    int i, j;
    for (i = 0; i < _size; ++i)
        for (j = 0; j < _size - 1; ++j)
            if (arr[j] > arr[j + 1])
            {
                int swp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swp;
            }
    //print(arr, _size);
}

int main()
{
    freopen("benchmark.txt", "a+", stdout);
    
    int k = 0;
    for (k = 0; k < 9; ++k)
    {
        double init = clock();
        
        int *a = (int*)malloc(N[k] * sizeof(int));
        srand(time(NULL));
        int i;
        for (i = 0; i < N[k]; ++i)
            *(a + i) = rand() % MOD;

        sort0(a, N[k]);
        //sort1(a, 0, N[k], N[k]);
        //sort2(a, N[k]);
        
        free(a);
        
        double _time = (clock() - init) / CLOCKS_PER_SEC;
        printf("%.3f ", _time);
        fflush(stdout); 
    }
    printf("\n");
    
    return 0;
}

