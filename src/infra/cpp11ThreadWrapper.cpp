#include "include/cpp11ThreadWrapper.h"
	
using namespace std;

Cpp11ThreadWrapper::Cpp11ThreadWrapper(thread&& t, RAIIAction action)
	: m_threadId(hash<thread::id>{}(this_thread::get_id()))
	, m_thread(move(t))
	, m_actionUponDestruction(action)
{
	
}

Cpp11ThreadWrapper::Cpp11ThreadWrapper(Cpp11ThreadWrapper&& other) noexcept
    : m_threadId(move(other.m_threadId))
	, m_thread(move(other.m_thread))
	, m_actionUponDestruction(move(other.m_actionUponDestruction))
{

}
    
Cpp11ThreadWrapper& Cpp11ThreadWrapper::operator=(Cpp11ThreadWrapper&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->m_threadId = other.m_threadId;
	this->m_thread = move(other.m_thread);
	this->m_actionUponDestruction = move(m_actionUponDestruction);

	other.m_threadId = 0;
	other.m_actionUponDestruction = nullptr;
	return *this;
}

Cpp11ThreadWrapper::~Cpp11ThreadWrapper()
{
	if (true == m_thread.joinable() && nullptr != m_actionUponDestruction)
	{
		(m_thread.*m_actionUponDestruction)();
	}
}

std::thread& Cpp11ThreadWrapper::GetThread()
{
	return m_thread;
}