#include <log4cxx/logger.h>

#include "include/posixCpp11ThreadWrapper.h"

using namespace std;

PosixCpp11ThreadWrapper::PosixCpp11ThreadWrapper(thread&& t, Cpp11ThreadWrapper::RAIIAction action) 
    : Cpp11ThreadWrapper(move(t), action)
{

}

PosixCpp11ThreadWrapper::~PosixCpp11ThreadWrapper()
{

}

PosixCpp11ThreadWrapper::PosixCpp11ThreadWrapper(PosixCpp11ThreadWrapper&& other) noexcept
    : Cpp11ThreadWrapper(move(other))
{

}

PosixCpp11ThreadWrapper& PosixCpp11ThreadWrapper::operator=(PosixCpp11ThreadWrapper&& rhs) noexcept
{
    if (this == &rhs)
    {
        return *this;
    }

    Cpp11ThreadWrapper::operator=(move(rhs));
    return *this;
}


bool PosixCpp11ThreadWrapper::SetAffinity(unsigned int cpuNum)
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

bool PosixCpp11ThreadWrapper::SetScheduling(int priority, int policy)
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
