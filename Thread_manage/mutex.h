#include "stdafx.h"
#pragma once

class Mutex
{
public:
    Mutex(DWORD dwSpinCount = 4000)
    {
        if (FALSE == ::InitializeCriticalSectionAndSpinCount(&cs, dwSpinCount))
        {
            abort();
        }
    };

    ~Mutex(){::DeleteCriticalSection(&cs);};
    void Lock() { ::EnterCriticalSection(&cs); };
    void UnLock() { ::LeaveCriticalSection(&cs); };
    BOOL TryLock() { return ::TryEnterCriticalSection(&cs); };
private:

protected:
    CRITICAL_SECTION cs;
};