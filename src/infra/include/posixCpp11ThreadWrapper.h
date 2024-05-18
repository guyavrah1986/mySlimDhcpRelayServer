// ============================================================================
// ============================================================================
// PosixCpp11ThreadWrapper:
// ------------------------
// This class is an implementation of its base class for POSIX based OS's.
// 
// ============================================================================
// ============================================================================
#pragma once

#include "cpp11ThreadWrapper.h"

class PosixCpp11ThreadWrapper : public Cpp11ThreadWrapper
{
public:
    PosixCpp11ThreadWrapper(std::thread&& t, RAIIAction action);
    virtual ~PosixCpp11ThreadWrapper();

    // Move semantics 
    PosixCpp11ThreadWrapper(PosixCpp11ThreadWrapper&& other) noexcept;
    PosixCpp11ThreadWrapper& operator=(PosixCpp11ThreadWrapper&& other) noexcept;
    
    // Abstract interface implementation
    virtual bool SetScheduling(int priority, int policy = -1);

private:
	sched_param m_schedulingParams;
};