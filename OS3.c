#include <stdio.h>
#include <stdlib.h>

#define NUM_CYCLES 2 * 1e8

// doing nothing 
void sleep(volatile unsigned int t)
{
    do t--;
    while(t != 0);
}

/*
 *  Statuses:
 *  0 - task done 
 *  1 - task running yet 
 */ 


int not_sipmle_task()
{
    static int i = 0;
    while (i < 6)
    {
        sleep(NUM_CYCLES);
        printf("Task0: running...\n");
        i++;
        return 1;
    }
    printf("Task0: done!\n");
    return 0;
}

int task1()
{
    sleep(NUM_CYCLES);
    printf("Task1: done!\n");
    return 0;
}

int task2()
{
    sleep(NUM_CYCLES);
    printf("Task2: done!\n");
    return 0;
}

int task3()
{
    sleep(NUM_CYCLES);
    printf("Task3: done!\n");
    return 0;
}

int task4()
{
    sleep(NUM_CYCLES);
    printf("Task4: done!\n");
    return 0;
}




int main(int argc, char **argv)
{
    //  queue if tasks
    int (*tasks_queue[5])() = {not_sipmle_task, task1, task2, task3, task4};

    // init status for each task
    int is_finished[5] = {0, 0, 0, 0, 0};

    int runnable = 1;
    // loop
    while (runnable)
    {
        runnable = 0;
        int i;
        for (i = 0; i < 5; ++i)
        {
            if (!is_finished[i]) // if cur task hasn't done yet 
            {
                // continue working 
                runnable = 1;

                // getting status 
                int status = tasks_queue[i]();

                // if task done - mark it
                if (status == 0)
                    is_finished[i] = 1;
            }
        }
    }
    return 0;
}

