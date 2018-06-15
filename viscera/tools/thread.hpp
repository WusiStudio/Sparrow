#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__

#include <functional>
#include <thread>

namespace ROOT_NAMESPACE
{

    typedef std::function< void(void *) > threadFunc;

    class thread
    {
    public: 
        thread( threadFunc p_run , void * p_flag  );
        void run( void );
    private:
        void loop( void * p_flag );
        std::thread * m_thread;
        threadFunc m_func;
    };
}

#include "achieve/thread.inl"

#endif //__THREAD_H__