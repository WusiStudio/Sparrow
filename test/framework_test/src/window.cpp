#include "window.h"
#include "tools/log.hpp"
#include "appaction.h"

#include "file.h"
#include "tools/md5.hpp"
#include "tools/md5.hpp"

namespace ROOT_NAMESPACE
{

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

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
        t_shader.retain();

        shaderProgramGLSL & t_shaderProgram = shaderProgramGLSL::Create( "a.vert", "a.frag" );
        t_shaderProgram.retain();
        m_shaderProgram = &t_shaderProgram;


        glGenVertexArrays( 1, &m_vao );
        glGenBuffers( 1, &m_vbo );
        glGenBuffers(1, &m_ebo );

        glBindVertexArray( m_vao );

        glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );


        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
        glEnableVertexAttribArray(0);

        glBindBuffer( GL_ARRAY_BUFFER, 0 ); 
        glBindVertexArray( 0 ); 

        return false;
    }

    void window::onTick( double p_dt )
    {

    }

    void window::onDraw( void )
    {
        m_shaderProgram->use();
        glBindVertexArray( m_vao );
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays( GL_TRIANGLES, 0, 3 );
    }
}