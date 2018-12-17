#include "Condition.h"
#include <stdio.h>

Condition::Condition()
    : mMutex()
    , mCond()
{
    if (pthread_mutex_init(&mMutex, NULL) != 0) {
        printf("init mutex fail!\n");
    }

    if (pthread_cond_init(&mCond, NULL) != 0) {
        printf("init cond fail!\n");
    }
}

Condition::~Condition()
{
    if (pthread_mutex_destroy(&mMutex) != 0) {
        printf("destroy mutex fail!\n");
    }

    if (pthread_cond_destroy(&mCond) != 0) {
        printf("destroy cond fail!\n");
    }
}

int Condition::lock()
{
    return pthread_mutex_lock(&mMutex);
}

int Condition::unlock()
{
    return pthread_mutex_unlock(&mMutex);
}

int Condition::wait()
{
    return pthread_cond_wait(&mCond, &mMutex);
}

int Condition::timeWait(const struct timespec* abstime)
{
    return pthread_cond_timedwait(&mCond, &mMutex, abstime);
}

int Condition::signal()
{
    return pthread_cond_signal(&mCond);
}

int Condition::broadcast()
{
    return pthread_cond_broadcast(&mCond);
}
