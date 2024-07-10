#include <log4cxx/logger.h>

#include "include/vrf.h"

using namespace std;

Vrf::Vrf(const string& interface)
{
    // TODO: add validation that this interface is valid!
    m_interfaceList.push_back(interface);
}

Vrf::~Vrf()
{

}