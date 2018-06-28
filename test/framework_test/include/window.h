#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "windowInterface.h"

namespace ROOT_NAMESPACE
{
    class window: public windowInterface
    {
    public:
        CREATEFUNC(window);
    protected:
        virtual bool init(void) override;
        

        virtual void onTick( double p_dt ) override;
        virtual void onDraw( void ) override;
    };
}


#endif //__WINDOW_H__