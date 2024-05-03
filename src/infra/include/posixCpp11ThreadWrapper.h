// ============================================================================
// ============================================================================
// PosixCpp11ThreadWrapper:
// ------------------------
// This class is an implementation of its base class for POSIX based OS's.
// 
// ============================================================================
// ============================================================================
#include "cpp11ThreadWrapper.h"

class PosixCpp11ThreadWrapper : public Cpp11ThreadWrapper
{
public:
    PosixCpp11ThreadWrapper(std::thread&& t, RAIIAction action);
    virtual ~PosixCpp11ThreadWrapper();
    virtual bool SetScheduling(int priority, int policy);

private:
	sched_param sch_params;
};