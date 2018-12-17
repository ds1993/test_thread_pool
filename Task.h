#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    Task();
    virtual ~Task();
    virtual void runTask(pthread_t tid) = 0;

    int getId();
private:
    static int mCount;
    int mId;
};

#endif
