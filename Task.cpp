#include "Task.h"

int Task::mCount = 0;

Task::Task()
    : mId(0)
{
    mId = mCount;
    ++mCount;
}

Task::~Task()
{
}

int Task::getId()
{
    return mId;
}
