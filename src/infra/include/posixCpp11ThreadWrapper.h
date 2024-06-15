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
    PosixCpp11ThreadWrapper(std::thread&& t, Cpp11ThreadWrapper::RAIIAction action);
    virtual ~PosixCpp11ThreadWrapper();

    // Copy semantics - disabled
	// =========================
    PosixCpp11ThreadWrapper(const PosixCpp11ThreadWrapper& other) = delete;
	PosixCpp11ThreadWrapper& operator=(const PosixCpp11ThreadWrapper& rhs) = delete;

	// Move semantics 
	// ==============
    PosixCpp11ThreadWrapper(PosixCpp11ThreadWrapper&& other) noexcept;
    PosixCpp11ThreadWrapper& operator=(PosixCpp11ThreadWrapper&& rhs) noexcept;

    // Abstract interface - implementation
	// ===================================
    bool SetAffinity(unsigned int cpuNum) override;
    bool SetScheduling(int priority, int policy = SCHED_OTHER) override;

};