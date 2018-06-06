#pragma once
#ifndef __BASICS_INTERFACE_H__
#define __BASICS_INTERFACE_H__

#include "imemory/object.hpp"

namespace ROOT_NAMESPACE
{
    class basicsInterface : public object
    {
    public:
        virtual void onTick( double p_dt ) = 0;
        virtual void onDraw( void ) = 0;
    };
}

#endif //__BASICS_INTERFACE_H__