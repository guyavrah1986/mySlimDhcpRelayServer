// ################################################################################
/*
* The motivation of having this wrapper class is to make sure that every 
* std::thread that is being created and executed will terminate gracefully on
* all paths.
* An example for an std::thread that  will NOT terminate gracefully is the 
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

	// Copy semantics - disabled
    Cpp11ThreadWrapper(const Cpp11ThreadWrapper& other) = delete;
	Cpp11ThreadWrapper& operator=(const Cpp11ThreadWrapper& rhs) = delete;

	// Move semantics 
    Cpp11ThreadWrapper(Cpp11ThreadWrapper&& other) noexcept;
    Cpp11ThreadWrapper& operator=(Cpp11ThreadWrapper&& other) noexcept;

	// Abstract interface
	virtual bool SetScheduling(int priority, int policy = SCHED_OTHER) = 0;

	// Getters and setters
	std::thread& GetThread();
	size_t GetThreadId() const { return this->m_threadId; }

protected:
	size_t m_threadId;

private:
	std::thread m_thread;
	RAIIAction m_actionUponDestruction;
};