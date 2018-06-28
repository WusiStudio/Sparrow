#include "appactionInterface.h"
#include "windowInterface.h"
#include "tools/log.hpp"

#if defined(OS_WINDOWS)
    #define PATH_SPACE "\\"
#else
    #define PATH_SPACE "/"
#endif

namespace ROOT_NAMESPACE
{

    appactionInterface * appactionInterface::sm_appaction = nullptr;

    appactionInterface & appactionInterface::instance( void )
    {
        return *sm_appaction;
    }

    const std::list< glm::ivec2 > appactionInterface::GetScreenSize()
    {
        std::list< glm::ivec2 > t_result;

        int t_monitorCount;
        GLFWmonitor ** t_pMonitor =  glfwGetMonitors( &t_monitorCount );

        LOG.info("Now, Screen number is ", t_monitorCount);
        for(int i = 0; i < t_monitorCount; i++){
            const GLFWvidmode * t_mode = glfwGetVideoMode( t_pMonitor[i] );

            LOG.info("Screen size is X: {0}, Y: {1}", t_mode->width, t_mode->height);

            t_result.push_back( glm::ivec2( t_mode->width, t_mode->height ) );
        }

        return t_result;
    }

    void appactionInterface::finish( void )
    {
        m_appactionRunning = false;
    }

    bool appactionInterface::init(void)
    {
        if( sm_appaction )
        {
            return true;
        }

        if( object::init() )
        {
            return true;
        }

        m_appactionPath = "";

        return false;
    }

    bool appactionInterface::initWithParameter( int p_argc, char ** p_argv )
    {
        if( startParameter( p_argc, p_argv ) )
        {
            return true;
        }

        if ( !glfwInit() )
        {
            return true;
        }

        //设置参数
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        //设置多重采样
        glfwWindowHint(GLFW_SAMPLES, 16);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

        sm_appaction = this;
        appactionStart();

        m_appactionTime = glfwGetTime();

        m_appactionRunning = true;

        //如果没有创建任何窗口 程序结束
        if( windowInterface::GetAll().size() <= 0 )
        {
            m_appactionRunning = false;
        }
        
        while( m_appactionRunning )
        {
            tick( glfwGetTime() - m_appactionTime );
            m_appactionTime = glfwGetTime();
            draw();

            if( windowInterface::GetAll().size() > 0 )
            {
                glfwPollEvents();
            }
            IMGCMake
        }

        appactionFinish();
        glfwTerminate();

        return false;
    }

    bool appactionInterface::destroy(void)
    {
        LOG.info("appactionInterface destroy");

        return object::destroy();
    }

    void appactionInterface::appactionStart( void )
    {
        IMSTACK
        onAppactionStart();
    }

    void appactionInterface::appactionFinish( void )
    {
        IMSTACK
        onAppactionFinish();
    }

    bool appactionInterface::startParameter( int p_argc, char ** p_argv )
    {

        //加载
        std::string t_appPath = p_argv[0];

        std::vector<std::string> t_list = split( t_appPath, PATH_SPACE );

        for( std::string & t_item : t_list )
        {
            LOG.info("dir: ", t_item);
        }

        return false;
    }

    void appactionInterface::tick( double p_dt )
    {
        for( basicsInterface * item : windowInterface::GetAll() )
        {
            item->tick( p_dt );
        }
    }
    void appactionInterface::draw( void )
    {
        for( basicsInterface * item : windowInterface::GetAll() )
        {
            item->draw();
        }
    }
}