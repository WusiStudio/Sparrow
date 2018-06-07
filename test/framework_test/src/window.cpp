#include "window.h"
#include "tools/log.hpp"
#include "appaction.h"

namespace ROOT_NAMESPACE
{
    bool window::init(void)
    {
        const glm::ivec2 t_screenSize = *appaction::GetScreenSize().begin();

        if( windowInterface::initWindow( "haha", glm::ivec2( t_screenSize.x, t_screenSize.y ), glm::ivec2(0) ) )
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