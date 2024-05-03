// ################################################################################
/*
* The motivation of having this wrapper class is to make sure that every 
* std::thread that is being created and executed will terminate gracefully on
* all path.
* An example for an std::thread that  will not terminate gracefully is the 
* following use case:
* {
*     std::thread t(someFunc);
*     // rest of code that does NOT join NOR detach the thread
* } --> this is where std::thread::terminate will be called (the thread is
 * destructed). 
* 
* The thread remained joinable and we call its terminate --> a crash will take
* place. This is the situation we wish/need to avoid! The wrapper class helps 
* us avoid that by checking in the destructor whether or not the thread is 
* "still joinable", and ONLY if it is the desired "action" on it will be called
* (either std::thread::join OR std::thread::detach) so that when the std::thread 
* destructor will be called, it will NOT sbe joinable, thus won't raise a crash
* of the program!
*/
// ################################################################################
#pragma once

#include <thread>

class Cpp11ThreadWrapper
{
public:
	typedef void (std::thread::*RAIIAction)();

	Cpp11ThreadWrapper(std::thread&& t, RAIIAction action);
	virtual ~Cpp11ThreadWrapper();
	std::thread& GetThread();

	// abstract interface
	virtual bool SetScheduling(int priority, int policy=-1) = 0;

protected:
	size_t m_threadId;

private:
	std::thread m_thread;
	RAIIAction m_actionUponDestruction;
};
