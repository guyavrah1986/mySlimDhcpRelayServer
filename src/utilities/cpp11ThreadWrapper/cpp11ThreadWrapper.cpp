#include "include/cpp11ThreadWrapper.h"
	
using namespace std;

cpp11ThreadWrapper::cpp11ThreadWrapper(thread&& t, RAIIAction a)
	: m_thread(move(t))
	, m_actionUponDestruction(a)
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
