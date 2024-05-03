#include <log4cxx/logger.h>

#include "include/posixCpp11ThreadWrapper.h"

using namespace std;

PosixCpp11ThreadWrapper::PosixCpp11ThreadWrapper(thread&& t, RAIIAction action)
    : Cpp11ThreadWrapper(move(t), action)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "created thread with thread ID:" << this->m_threadId);
}

PosixCpp11ThreadWrapper::~PosixCpp11ThreadWrapper()
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "destroyed thread with thread ID:" << this->m_threadId);
}

bool PosixCpp11ThreadWrapper::SetScheduling(int priority, int policy)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    // TODO: validate arguments!
    sch_params.sched_priority = priority;
    if (pthread_setschedparam(this->GetThread().native_handle(), policy, &sch_params))
	{
        LOG4CXX_ERROR(rootLogger, "Failed to set thread :");
        return false;
    }

    LOG4CXX_INFO(rootLogger, "set  thread scheduling priority:" << priority);
    return true;
}

