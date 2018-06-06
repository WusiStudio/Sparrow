#include "window.h"
#include "tools/log.hpp"

namespace ROOT_NAMESPACE
{
    bool window::init(void)
    {
        if( windowInterface::init() )
        {
            return true;
        }

        return false;
    }

    void window::onTick( double p_dt )
    {
        windowInterface::onTick( p_dt );
    }

    void window::onDraw( void )
    {

    }
}