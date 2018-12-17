#ifndef CTHREAD_H
#define CTHREAD_H

#include <pthread.h>

class CThread {
public:
    CThread();
    virtual ~CThread();
    int start();
    int join();
    pthread_t getTid();
private:
    virtual void run() = 0;
    static void* threadFunc(void* arg);

    pthread_t mTid;
};

#endif
