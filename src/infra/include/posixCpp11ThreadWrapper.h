// ============================================================================
// ============================================================================
// PosixCpp11ThreadWrapper:
// ------------------------
// This class is an implementation of its base class for POSIX based OS's.
// 
// ============================================================================
// ============================================================================
#pragma once

#include <log4cxx/logger.h>

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
    bool SetAffinity(unsigned int cpuNum) override
    {   
        auto rootLogger = log4cxx::Logger::getRootLogger();
        if (false == IsValidCpuNum(cpuNum))
        {
            LOG4CXX_ERROR(rootLogger, "got an invlid CPU num");
            return false;
        }

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

        LOG4CXX_DEBUG(rootLogger, "set thread:" << this->GetThread().native_handle() 
                      << " on CPU:" << cpuNum);

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