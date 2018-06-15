#pragma once
#ifndef __THREAD_INL__
#define __THREAD_INL__

#include <thread>

namespace ROOT_NAMESPACE
{
    thread::thread( std::function< void(void *) > p_run, void * p_flag )
    {
        m_func = p_run;
        m_thread = new std::thread( &thread::loop, this, p_flag );
    }

    void thread::run( void )
    {
        m_thread->join();
    }

    void thread::loop( void * p_flag )
    {
        m_func( p_flag );
    }
}

#endif //__THREAD_INL__