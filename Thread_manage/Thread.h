#include "stdafx.h"
#pragma once

class CallbackBase
{
public:
    virtual DWORD Run() = 0;
    virtual ~CallbackBase() {};
};

template<typename T>
class CallbackP0 : public CallbackBase
{
public:
    typedef DWORD (T::*Method)();
    CallbackP0(T* pObj, Method func) :m_pObj(pObj),m_pFunc(func){};

    DWORD Run() { return (m_pObj->*m_pFunc)(); };
private:
    T*          m_pObj;
    Method      m_pFunc;
};

template<typename T, typename P1>
class CallbackP1 : public CallbackBase
{
public:
    typedef DWORD(T::*Method)(P1);
    CallbackP1(T* pObj, Method func) :m_pObj(pObj), m_pFunc(func) {};
    void setParam(P1 p1) { m_P1 = p1; };
    DWORD Run() { return (m_pObj->*m_pFunc)(m_P1); };
private:
    T * m_pObj;
    Method      m_pFunc;
    P1 m_P1;
};

template<typename T, typename P1, typename P2>
class CallbackP2 : public CallbackBase
{
public:
    typedef DWORD(T::*Method)(P1,P2);
    CallbackP2(T* pObj, Method func) :m_pObj(pObj), m_pFunc(func) {};

    void setParam(P1 p1, P2 p2) { m_P1 = p1; m_P2 = p2; };
    DWORD Run() { return (m_pObj->*m_pFunc)(m_P1,m_P2); };
private:
    T * m_pObj;
    Method      m_pFunc;
    P1 m_P1;
    P2 m_P2;
};

template<typename T, typename P1, typename P2, typename P3>
class CallbackP3 : public CallbackBase
{
public:
    typedef DWORD(T::*Method)(P1,P2,P3);
    CallbackP3(T* pObj, Method func) :m_pObj(pObj), m_pFunc(func) {};

    void setParam(P1 p1, P2 p2, P3 p3) { m_P1 = p1; m_P2 = p2; m_P3 = p3; };
    DWORD Run() { return (m_pObj->*m_pFunc)(m_P1,m_P2,m_P3); };
private:
    T * m_pObj;
    Method      m_pFunc;
    P1 m_P1;
    P2 m_P2;
    P3 m_P3;
};

class Thread
{
public:
    Thread() {};
    ~Thread() {};

    void run()
    {
        while (1)
        {
            Sleep(1);
            if (NULL != m_pNextTask)
            {
                m_pNextTask->Run();
                m_pNextTask = NULL;
            }
        }
    };

    void stop() {};
    BOOL IsBusy() { return NULL != m_pNextTask; }
    void setTask(CallbackBase *pTask) { m_pNextTask = pTask; };

    DWORD dwID;
    DWORD dwThreadID;
private:
    CallbackBase * m_pNextTask;

};