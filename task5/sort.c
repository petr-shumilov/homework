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
    if (count == NULL)
    {
        printf("ERROR: couldn't allocate memory");
        exit(1);
    }
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


void sort1(int *arr, int _size)
{
    long i, j, lb, ub, starrckpos = 1, ppos, pivot, temp;
    long *lbstarrck = (long*)malloc(sizeof(long) * 2048);
    long *ubstarrck = (long*)malloc(sizeof(long) * 2048);
    if (lbstarrck == NULL || ubstarrck == NULL)
    {
        printf("ERROR: couldn't allocate memory");
        exit(1);
    } 
    lbstarrck[1] = 0;
    ubstarrck[1] = _size - 1;
    do
    {
        lb = lbstarrck[starrckpos];
        ub = ubstarrck[starrckpos];
        starrckpos--;
        do
        {
            ppos = (lb + ub) >> 1;
            i = lb;
            j = ub;
            pivot = arr[ppos];
            do
            {
                while (arr[i] < pivot) i++;
                while (pivot < arr[j]) j--;
                if (i <= j)
                {
                    temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
                    i++; j--;
                }
            } while (i <= j);
            
            if (i < ppos)
            {     
                if (i < ub )
                {   
                    starrckpos++;     
                    lbstarrck[starrckpos] = i;
                    ubstarrck[starrckpos] = ub;
                }
                ub = j;             
            }
            else
            {
                if (j > lb)
                { 
                    starrckpos++;
                    lbstarrck[starrckpos] = lb;
                    ubstarrck[starrckpos] = j;
                }
                lb = i;
            }
        } while (lb < ub);       
    } while (starrckpos);  
}


void sort2(int *arr, int _size) //O(n ^ 2)
{
    if (_size > 1e5)
    {
        printf(" n/a ");
        return;
    }
    int i, j;
    for (i = 0; i < _size; ++i)
        for (j = 0; j < _size - 1; ++j)
            if (arr[j] > arr[j + 1])
            {
                int swp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swp;
            }
}


int main()
{

    freopen("benchmark.txt", "w+", stdout);

    void (*sorting_func[3])(int *arr, int _size) = {sort0, sort1, sort2};
    char *header = "          |  5  | 10  | 100 | 1e3 | 1e4 | 1e5 | 1e6 | 1e7 | 1e8 |";
    char *li[3] = {"O(n)       ", "O(n log n) ", "O(n ^ 2)   " };
    
    int f;
    printf("BENCHMARK OF SORTINGS\n%s\n", header);
    for (f = 0; f < 3; ++f)
    {
        printf("%s", li[f]);
        int k;
        for (k = 0; k < 9; ++k)
        {
            int *a = (int*)malloc(N[k] * sizeof(int));
            if (a == NULL)
            {
                printf("ERROR: couldn't allocate memory");
                exit(1);
            }
            srand(time(NULL));
            int i;
            for (i = 0; i < N[k]; ++i)
                a[i] = rand() % MOD;

            double init = clock();
            sorting_func[f](a, N[k]);
            double _time = (clock() - init) / CLOCKS_PER_SEC;
            
            free(a);
            if (f == 2 && N[k] > 1e5)
                continue;
            printf("%.3f ", _time);
            fflush(stdout); 
        }
        printf("\n");
    }
    
    return 0;
}

