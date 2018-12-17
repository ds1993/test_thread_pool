#ifndef CONDITION_H
#define CONDITION_H

#include <pthread.h>

class Condition {
public:
    Condition();
    ~Condition();

    int lock();
    int unlock();
    int wait();
    int timeWait(const struct timespec* abstime);
    int signal();
    int broadcast();
private:
    pthread_mutex_t mMutex;
    pthread_cond_t mCond;
};

#endif
