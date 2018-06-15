#include "windowInterface.h"
#include "appactionInterface.h"

namespace ROOT_NAMESPACE
{
    std::list<windowInterface *> windowInterface::sm_windowList;

    const std::list<windowInterface *> windowInterface::GetAll()
    {
        return sm_windowList;
    }

    bool windowInterface::isExist( windowInterface * p_window )
    {
        for( windowInterface  * item : sm_windowList )
        {
            if( item == p_window )
            {
                return true;
            }
        }

        return false;
    }

    bool windowInterface::initWindow( const std::string & p_name, const glm::ivec2 & p_size, const glm::ivec2 & p_position )
    {
        if( object::init() )
        {
            return true;
        }

        m_fps = 0;
        m_prveTime = time( &m_prveTime );

        LOG.info("time: ", m_prveTime);

        m_glfwWindow = glfwCreateWindow(p_size.x, p_size.y, p_name.c_str(), NULL, NULL);

        if (!m_glfwWindow)
        {
            LOG.info("create window faild");
            glfwTerminate();
            return true;
        }

        glfwSetWindowPos(m_glfwWindow, p_position.x, p_position.y );

        retain();
        sm_windowList.push_back( this );

        return false;
    }

    bool windowInterface::init(void)
    {
        if( object::init() )
        {
            return true;
        }

        return false;
    }

    void windowInterface::onTick( double p_dt )
    {
        IMSTACK
        time_t t_time;
        time(&t_time);
        if( t_time != m_prveTime )
        {
            LOG.info("{0} fps: {1}", this, m_fps / (t_time - m_prveTime) );
            m_prveTime = t_time;
            m_fps = 0;
        }
        m_fps++;

        if( glfwWindowShouldClose( m_glfwWindow ) )
        {
            sm_windowList.remove( this );

            release();

            glfwDestroyWindow( m_glfwWindow );
            m_glfwWindow = nullptr;

            // 窗口关闭 退出app
            if( sm_windowList.size() <= 0 )
            {
                appactionInterface::instance().finish();
            }
            return;
        }
    }

    void windowInterface::onDraw( void )
    {
        IMSTACK
        glfwMakeContextCurrent( m_glfwWindow );
        glfwSwapInterval(0);

        // glViewport(0, 0, width, height);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers( m_glfwWindow );
        // LOG.info("draw");
    }

    bool windowInterface::destroy()
    {
        LOG.info("windowInterface destroy");
        return object::destroy();
    }
}