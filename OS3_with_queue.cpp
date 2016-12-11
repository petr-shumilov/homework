#include <iostream>
#include <list>

#define end 0
#define start 1

using namespace std;

typedef void (*process_t)(int*);


struct Process
{
    process_t proc;
    int argv;
    Process ( process_t _proc, int _argv) : proc(_proc), argv(_argv) {} 
};

list <Process > proc_queue;

void _sleep(volatile unsigned int t)
{
    do t--;
    while(t != 0);
}


void task0(int *argv)
{
    while (*argv < 4)
    {
        _sleep(1e8 * 2);
        cout << "Task0: IP " << *argv << "\n";
        (*argv)++;
        return;
    }
    *argv = end;
}

void task1(int *argv)
{
    _sleep(1e8 * 2);
    cout << "Task1 done!\n";
    *argv = end;
}

void task2(int *argv)
{
    _sleep(1e8 * 2);
    cout << "Task2 done!\n";
    *argv = end;
}

void task3(int *argv)
{
    _sleep(1e8 * 2);
    cout << "Task3 done!\n";
    *argv = end;
}

void task4(int *argv)
{
    _sleep(1e8 * 2);
    cout << "Task4 done!\n";
    *argv = end;
}

void init()
{
    // example
    proc_queue.push_back(Process(&task0, start));
    proc_queue.push_back(Process(&task1, start));
    proc_queue.push_back(Process(&task2, start));
    proc_queue.push_back(Process(&task3, start));
    proc_queue.push_back(Process(&task4, start));
    proc_queue.push_back(Process(&task0, start));
}

void FIFO()
{
    while (!proc_queue.empty())
    {
        // getting top proc
        Process temp = proc_queue.front();
        proc_queue.pop_front();

        temp.proc(&temp.argv); // executing 
        
        if (temp.argv) // if not done 
            proc_queue.push_back(temp);
    }
}

void FILO()
{
    while (!proc_queue.empty())
    {
        Process temp = proc_queue.back();
        proc_queue.pop_back();

        temp.proc(&temp.argv);
        
        if (temp.argv)
            proc_queue.push_back(temp);
    }
}

int main()
{
    init();

    cout << "Choose:\n1)FIFO\n2)FILO\n";

    int strategy;
    cin >> strategy;
    
    if (strategy == 1)
        FIFO();
    else if (strategy == 2)
        FILO();
        
    return 0;
}