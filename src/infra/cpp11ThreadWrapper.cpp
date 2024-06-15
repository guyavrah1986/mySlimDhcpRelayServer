#include "include/cpp11ThreadWrapper.h"

using namespace std;

Cpp11ThreadWrapper::Cpp11ThreadWrapper(thread&& t, RAIIAction action)
	: m_thread(std::move(t))
	, m_actionUponDestruction(action)
{
		
}

Cpp11ThreadWrapper::~Cpp11ThreadWrapper()
{
    if (true == m_thread.joinable() && nullptr != m_actionUponDestruction)
	{
		(m_thread.*m_actionUponDestruction)();
	}
}

Cpp11ThreadWrapper::Cpp11ThreadWrapper(Cpp11ThreadWrapper&& other) noexcept
	: m_actionUponDestruction(move(other.m_actionUponDestruction))
{

}
	
Cpp11ThreadWrapper& Cpp11ThreadWrapper::operator=(Cpp11ThreadWrapper&& rhs) noexcept
{
    if (this == &rhs)
	{
		return *this;
	}

	this->m_thread = move(rhs.m_thread);
	this->m_actionUponDestruction = move(m_actionUponDestruction);
	rhs.m_actionUponDestruction = nullptr;
	return *this;
}

bool Cpp11ThreadWrapper::IsValidCpuNum(unsigned int cpuNum) const
{
	if (cpuNum > thread::hardware_concurrency())
	{
		return false;
	}

	return true;
}