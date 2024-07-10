#include <log4cxx/logger.h>

#include "include/vrf.h"

using namespace std;

Vrf::Vrf(const vector<string>& interfacesList)
{
    // TODO: add validation that this interface is valid!
    for (auto interface : interfacesList)
    {
        m_interfaceList.push_back(interface);
    }
}

Vrf::~Vrf()
{
    m_interfaceList.clear();
}

Result Vrf::SetInterfaces()
{
   	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger,"about to create IN socket for each interface in the VRF");
    if (true == m_interfaceList.empty())
    {
        return Result(ErrorCode::UTILS_ERROR_CODE_NO_INTERFACE);
    }

    return Result(ErrorCode::UTILS_ERROR_CODE_GENERAL_FAUILRE);
}