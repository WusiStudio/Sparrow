#pragma once
#ifndef __BASICS_INTERFACE_H__
#define __BASICS_INTERFACE_H__

#include "imemory/object.hpp"

namespace ROOT_NAMESPACE
{
    class basicsInterface : public object
    {
    protected:
        virtual void onTick( double p_dt );
        virtual void onDraw( void );
    };
}

#endif //__BASICS_INTERFACE_H__