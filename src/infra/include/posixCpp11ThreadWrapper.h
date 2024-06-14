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

class PosixCpp11ThreadWrapper : public Cpp11ThreadWrapper
{
public:
    PosixCpp11ThreadWrapper(std::thread&& t, Cpp11ThreadWrapper::RAIIAction action) 
        : Cpp11ThreadWrapper(std::move(t), action)
    {

    }

    // Abstract interface - implementation
	// ===================================
    bool SetAffinity(int cpuNum = -1) override
    {   
        // TODO: implement validation of the argument
        // in the base class!
        auto rootLogger = log4cxx::Logger::getRootLogger();
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(cpuNum, &cpuset);
        int retCode = pthread_setaffinity_np(this->GetThread().native_handle(),
                                        sizeof(cpu_set_t), &cpuset);
        if (0 != retCode)
        {
            LOG4CXX_ERROR(rootLogger, "got error return code:" << retCode 
                << " and was unable to set thread's affinity");
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
};