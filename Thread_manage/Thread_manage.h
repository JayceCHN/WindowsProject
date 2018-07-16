#pragma once
#include "stdafx.h"
#include "mutex.h"
#include "Thread.h"

class Thread_manage
{
public:
	Thread_manage();
	~Thread_manage();

    DWORD AddTask(CallbackBase* pTask);
    void setThreadFree(DWORD dwID);
    BOOL CloseThreadManage();

    void getThreadNum(int &nBusyNum, int &nAllNum);
private:
    BOOL AddThreadPool();
    BOOL ReduceThreadPool();
    DWORD UpdateBusyNum();
    Thread* FindThread();

    DWORD m_dwThreadID;
    DWORD m_dwThreadAllNum;
    DWORD m_dwThreadBusyNum;
    Mutex m_Mutex;
    std::map<DWORD, Thread*> m_mapThread;
};

