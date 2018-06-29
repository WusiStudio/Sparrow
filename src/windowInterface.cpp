#include "glad/glad.h"
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

        glfwMakeContextCurrent( m_glfwWindow );
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        //启用多重采样
        glEnable(GL_MULTISAMPLE);

        //判断多重采样是否启用成功
        if(glIsEnabled(GL_MULTISAMPLE))
        {
            GLint buffers ,samples;
            glGetIntegerv(GL_SAMPLE_BUFFERS,&buffers);
            glGetIntegerv(GL_SAMPLES,&samples);

            if(buffers > 0 && samples > 0)
            {
                LOG.info("Enabled Multisample! buffers: {0}, samples: {1}", buffers, samples);
            }    
        }
        
        //启用深度测试
        glEnable(GL_DEPTH_TEST);
        if(glIsEnabled(GL_DEPTH_TEST))
        {
            LOG.info("Enabled Depth Test!");
        }

        //启用图元重启
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xFFFF);
        if(glIsEnabled(GL_PRIMITIVE_RESTART))
        {
            LOG.info("Enabled Primitive Restart!");
        }

        //启用混合
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

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


    void windowInterface::tick( double p_dt )
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

        onTick( p_dt );
    }

    void windowInterface::draw( void )
    {
        IMSTACK
        glfwMakeContextCurrent( m_glfwWindow );
        glfwSwapInterval(0);

        // glViewport(0, 0, width, height);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        onDraw();

        glfwSwapBuffers( m_glfwWindow );
        // LOG.info("draw");
    }

    bool windowInterface::destroy()
    {
        LOG.info("windowInterface destroy");
        return object::destroy();
    }
}