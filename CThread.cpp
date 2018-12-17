#include "CThread.h"

CThread::CThread()
    : mTid(0)
{
}

CThread::~CThread()
{
}

int CThread::start()
{
    return pthread_create(&mTid, NULL, threadFunc, this);
}

int CThread::join()
{
    return pthread_join(mTid, NULL);
}

pthread_t CThread::getTid()
{
    return mTid;
}

void* CThread::threadFunc(void* arg)
{
    CThread* context = (CThread*)arg;
    context->run();
    return NULL;
}
