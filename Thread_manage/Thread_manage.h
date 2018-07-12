#pragma once
#include "stdafx.h"
#include "mutex.h"

class Thread_manage
{
public:
	Thread_manage();
	~Thread_manage();

    DWORD AddTask(CallbackBase* pTask);
    void setThreadFree(DWORD dwID);
    BOOL CloseThreadManage();
private:
    BOOL AddThreadPool();
    BOOL ReduceThreadPool();
    Thread* FindThread();

    DWORD m_dwThreadID;
    DWORD m_dwThreadAllNum;
    DWORD m_dwThreadBusyNum;
    Mutex m_Mutex;
    std::map<DWORD, Thread*> m_mapThread;
};

