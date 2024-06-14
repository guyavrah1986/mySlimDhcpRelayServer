// ============================================================================
// ============================================================================
// PosixCpp11ThreadWrapper:
// ------------------------
// This class is an implementation of its base class for POSIX based OS's.
// 
// ============================================================================
// ============================================================================
#pragma once

#include "cpp11ThreadWrapper.h"

template <typename T>
class PosixCpp11ThreadWrapper : public Cpp11ThreadWrapper<T>
{
public:
    PosixCpp11ThreadWrapper(std::thread&& t, Cpp11ThreadWrapper<T>::RAIIAction action) 
        : Cpp11ThreadWrapper<T>(std::move(t), action)
    {

    }

    // Abstract interface - implementation
	// ===================================
    T GetThreadId() const override
    {
        return this->m_threadId;
    }

    bool SetAffinity(int cpuNum = -1) override
    {
        if (-1 == cpuNum)
        {
            return false;
        }

        return true;
    }

    bool SetScheduling(int priority, int policy = SCHED_OTHER) override
    {
        if (priority < 100)
        {
            return true;
        }
        else if (policy > 200)
        {
            return true;
        }

        return false;
    }

    /*
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(i, &cpuset);
    int rc = pthread_setaffinity_np(threads[i].native_handle(),
                                    sizeof(cpu_set_t), &cpuset);
    */
};