#include "window.h"
#include "tools/log.hpp"
#include "appaction.h"

#include "file.h"
#include "tools/md5.hpp"
#include "tools/md5.hpp"
#include "shaderGLSL.h"

namespace ROOT_NAMESPACE
{
    bool window::init(void)
    {
        const glm::ivec2 t_screenSize = *appaction::GetScreenSize().begin();

        if( windowInterface::initWindow( "haha", glm::ivec2( 800, 600 ), glm::ivec2( (t_screenSize.x - 800) / 2, (t_screenSize.y - 600) / 2 ) ) )
        {
            return true;
        }

        LOG.info( "{0}: ", appaction::instance().assetsPath() + "shader/a.vert", file::ReadAllText( appaction::instance().assetsPath() + "shader/a.vert" ) );
        LOG.info( "md5: ", md5( file::ReadAllText( appaction::instance().assetsPath() + "shader/a.vert" ) ).digest() );

        std::ifstream t_ifs;
        t_ifs.open( appaction::instance().assetsPath() + "shader/a.vert" , std::ios::binary );
        LOG.info( "md5: ", md5( t_ifs ).digest() );

        LOG.info( "md5: ", file::MD5( appaction::instance().assetsPath() + "shader/a.vert" ) );

        shaderGLSL & t_shader = shaderGLSL::Create( "a.vert" );

        return false;
    }

    void window::onTick( double p_dt )
    {

    }

    void window::onDraw( void )
    {

    }
}