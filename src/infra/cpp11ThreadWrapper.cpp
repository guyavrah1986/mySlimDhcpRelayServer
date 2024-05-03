#include "include/cpp11ThreadWrapper.h"
	
using namespace std;

Cpp11ThreadWrapper::Cpp11ThreadWrapper(thread&& t, RAIIAction action)
	: m_thread(move(t))
	, m_actionUponDestruction(action)
{

}

Cpp11ThreadWrapper::~Cpp11ThreadWrapper()
{
	if (m_thread.joinable())
	{
		(m_thread.*m_actionUponDestruction)();
	}
}

std::thread& Cpp11ThreadWrapper::GetThread()
{
	return m_thread;
}