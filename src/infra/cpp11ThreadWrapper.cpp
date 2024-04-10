#include "include/cpp11ThreadWrapper.h"
	
using namespace std;

cpp11ThreadWrapper::cpp11ThreadWrapper(thread&& t, RAIIAction action)
	: m_thread(move(t))
	, m_actionUponDestruction(action)
{

}

cpp11ThreadWrapper::~cpp11ThreadWrapper()
{
	if (m_thread.joinable())
	{
		(m_thread.*m_actionUponDestruction)();
	}
}

std::thread& cpp11ThreadWrapper::GetThread()
{
	return m_thread;
}
