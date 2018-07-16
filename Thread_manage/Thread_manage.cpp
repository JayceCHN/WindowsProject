#include "stdafx.h"
#include "Thread.h"
#include "Thread_manage.h"

#define THREAD_NUM 5

//
unsigned int  __stdcall ThreadProc(LPVOID pParam)
{
    //Ïß³ÌÖ´ÐÐ
    Thread* pThread = (Thread*)pParam;
    pThread->run();
    return 0;
}


Thread_manage::Thread_manage()
{
    m_dwThreadID = 0;
    m_dwThreadAllNum = 0;
    m_dwThreadBusyNum = 0;
    AddThreadPool();
    CallbackP0<Thread_manage> *pC = new CallbackP0<Thread_manage>(this, &Thread_manage::UpdateBusyNum);
    AddTask(pC);
}


Thread_manage::~Thread_manage()
{
    CloseThreadManage();
}

DWORD Thread_manage::AddTask(CallbackBase * pTask)
{
    if (m_dwThreadBusyNum == m_dwThreadAllNum)
    {
        AddThreadPool();
    }
    Thread* pThread = FindThread();
    while (NULL == pThread)
    {
        AddThreadPool();
        pThread = FindThread();
    }
    pThread->setTask(pTask);
    m_Mutex.Lock();
    m_dwThreadBusyNum++;
    m_Mutex.UnLock();

    ReduceThreadPool();
    return 0;
}

void Thread_manage::setThreadFree(DWORD dwID)
{
    m_Mutex.Lock();
    m_dwThreadBusyNum--;
    m_Mutex.UnLock();
}

BOOL Thread_manage::CloseThreadManage()
{
    for (std::map<DWORD, Thread*>::iterator iter = m_mapThread.begin(); iter != m_mapThread.end();)
    {
        DWORD ID = iter->first;
        iter++;
        m_mapThread.erase(ID);
    }
    return 0;
}

void Thread_manage::getThreadNum(int & nBusyNum, int & nAllNum)
{
    nBusyNum = m_dwThreadBusyNum;
    nAllNum = m_dwThreadAllNum;
}

BOOL Thread_manage::AddThreadPool()
{
    for (size_t i = 0; i < THREAD_NUM; i++)
    {
        DWORD dwThreadID = 0;
        Thread* pThread = new Thread();
        HANDLE hHandle = (HANDLE)_beginthreadex(NULL, 0, &ThreadProc, (LPVOID)pThread, 0, (unsigned int*)&dwThreadID);

        if (0 == hHandle)
        {
            delete(pThread);
            continue;
        }
        m_Mutex.Lock();
        pThread->dwID = m_dwThreadID;
        pThread->dwThreadID = dwThreadID;
        m_dwThreadAllNum++;
        m_mapThread.insert(std::make_pair(m_dwThreadID, pThread));
        m_dwThreadID++;
        m_Mutex.UnLock();
    }
    return 0;
}

BOOL Thread_manage::ReduceThreadPool()
{
    m_Mutex.Lock();
    if (m_dwThreadAllNum > THREAD_NUM && (m_dwThreadAllNum - m_dwThreadBusyNum) >= THREAD_NUM)
    {
        DWORD dwReduceNum = 0;
        DWORD dwReduce[THREAD_NUM];
        for (std::map<DWORD, Thread*>::iterator iter = m_mapThread.begin(); iter != m_mapThread.end(); iter++)
        {
            if (!iter->second->IsBusy())
            {
                dwReduce[dwReduceNum] = iter->first;
                dwReduceNum++;
                if (dwReduceNum == THREAD_NUM) { m_dwThreadAllNum -= THREAD_NUM; break; }
            }
        }
        for (size_t i = 0; i < THREAD_NUM; i++)
        {
            m_mapThread.erase(dwReduce[i]);
        }
    }
    m_Mutex.UnLock();
    return 0;
}

DWORD Thread_manage::UpdateBusyNum()
{
    while (1)
    {
        Sleep(1);
        DWORD dwNum = 0;
        m_Mutex.Lock();
        ReduceThreadPool();
        for (std::map<DWORD, Thread*>::iterator iter = m_mapThread.begin(); iter != m_mapThread.end(); iter++)
        {
            if (iter->second->IsBusy())
            {
                dwNum++;
            }
        }
        m_dwThreadBusyNum = dwNum;
        m_Mutex.UnLock();
    }
    return 0;
}

Thread * Thread_manage::FindThread()
{
    m_Mutex.Lock();
    for (std::map<DWORD, Thread*>::iterator iter = m_mapThread.begin(); iter != m_mapThread.end(); iter++)
    {
        if (!iter->second->IsBusy())
        {
            m_Mutex.UnLock();
            return iter->second;
        }
    }
    m_Mutex.UnLock();
    return NULL;
}
