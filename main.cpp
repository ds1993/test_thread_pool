#include "ThreadPool.h"
#include <unistd.h>
#include <stdio.h>

class MyTask: public Task {
public:
    MyTask() {}
    virtual ~MyTask() {}
    virtual void runTask(pthread_t tid)
    {
        printf("tid: %ld, task id: %d\n", tid, getId());
        sleep(5);
    }
};

int main()
{
    ThreadPool threadPool;
    for (int i = 0; i < 20; ++i) {
        MyTask* task = new MyTask();
        threadPool.addTask(task);
    }
    sleep(10);
    threadPool.stopAll();
}
