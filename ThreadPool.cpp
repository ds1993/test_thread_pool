#include "ThreadPool.h"
#include <malloc.h>
#include <stdio.h>

ThreadPool::ThreadPool()
    : mCond()
    , mTaskList()
    , mMaxThreads(10)
    , mFreeThreadNum(0)
    , mQuit(false)
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::addTask(Task* task)
{
    mCond.lock();
    mTaskList.push_back(task);
    if (mFreeThreadNum > 0) {
        mCond.signal();
    }
    else if ((mFreeThreadNum == 0) && (mThreadList.size() < mMaxThreads)) {
        CWorkThread* thread = new CWorkThread(this);
        thread->start();
        mThreadList.push_back(thread);
    }
    else {
        printf("number of thread is max, wait a thread end!\n");
    }
    mCond.unlock();
}

void ThreadPool::stopAll()
{
    mCond.lock();
    std::list<CWorkThread*> threadList = mThreadList;
    mQuit = true;
    mCond.broadcast();
    mCond.unlock();
    for (auto it = threadList.begin(); it != threadList.end(); ++it) {
        (*it)->join();
    }
    while (mThreadList.begin() != mThreadList.end()) {
        CWorkThread* thread = *(mThreadList.begin());
        mThreadList.pop_front();
        delete thread;
    }
    while(mTaskList.begin() != mTaskList.end()) {
        Task* task = *(mTaskList.begin());
        mTaskList.pop_front();
        delete task;
    }
}

ThreadPool::CWorkThread::CWorkThread(ThreadPool* context)
    : mContext(context)
{
}

ThreadPool::CWorkThread::~CWorkThread()
{
}

void ThreadPool::CWorkThread::run()
{
    mContext->ThreadRun(getTid());
}

void ThreadPool::ThreadRun(pthread_t tid)
{
    while (1) {
        mCond.lock();
        if (mQuit == true) {
            mCond.unlock();
            break;
        }
        if (mTaskList.size() == 0) {
            ++mFreeThreadNum;
            mCond.wait();
            --mFreeThreadNum;
        }
        Task* task = NULL;
        if (mTaskList.size() != 0) {
            task = *(mTaskList.begin());
            mTaskList.pop_front();
        }
        mCond.unlock();
        if (task != NULL) {
            task->runTask(tid);
            delete task;
        }
    }
    printf("thread %ld exit\n", tid);
}
