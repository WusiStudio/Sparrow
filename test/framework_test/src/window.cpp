#include "window.h"
#include "tools/log.hpp"
#include "appaction.h"

#include "file.h"
#include "tools/md5.hpp"

namespace ROOT_NAMESPACE
{
    bool window::init(void)
    {
        const glm::ivec2 t_screenSize = *appaction::GetScreenSize().begin();

        if( windowInterface::initWindow( "haha", glm::ivec2( 800, 600 ), glm::ivec2( (t_screenSize.x - 800) / 2, (t_screenSize.y - 600) / 2 ) ) )
        {
            return true;
        }

        LOG.info( "/Users/wusi/Projects/Sparrow/README.md: ", file::ReadAllText( "/Users/wusi/Projects/Sparrow/README.md" ) );
        LOG.info( "md5: ", md5( file::ReadAllText( "/Users/wusi/Projects/Sparrow/README.md" ) ).digest() );

        std::ifstream t_ifs;
        t_ifs.open( "/Users/wusi/Projects/Sparrow/README.md" );
        LOG.info( "md5: ", md5( t_ifs ).digest() );

        // LOG.info( "md5: ", file::MD5( "/Users/wusi/Projects/Sparrow/README.md" ) );

        return false;
    }

    void window::onTick( double p_dt )
    {

    }

    void window::onDraw( void )
    {

    }
}