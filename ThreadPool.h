#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "Condition.h"
#include "CThread.h"
#include "Task.h"
#include <list>

class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();
    void addTask(Task* task);
    void stopAll();
private:
    class CWorkThread: public CThread {
    public:
        CWorkThread(ThreadPool* context);
        virtual ~CWorkThread();
        virtual void run();
    private:
        ThreadPool* mContext;
    };

    void ThreadRun(pthread_t tid);

    Condition mCond;
    std::list<CWorkThread*> mThreadList;
    std::list<Task*> mTaskList;
    int mMaxThreads;
    int mFreeThreadNum;
    bool mQuit;
};

#endif
