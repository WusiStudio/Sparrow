#include "window.h"
#include "tools/log.hpp"
#include "appaction.h"

namespace ROOT_NAMESPACE
{
    bool window::init(void)
    {
        const glm::ivec2 t_screenSize = *appaction::GetScreenSize().begin();

        if( windowInterface::initWindow( "haha", glm::ivec2( 800, 600 ), glm::ivec2( (t_screenSize.x - 800) / 2, (t_screenSize.y - 600) / 2 ) ) )
        {
            return true;
        }

        return false;
    }

    void window::onTick( double p_dt )
    {

    }

    void window::onDraw( void )
    {

    }
}