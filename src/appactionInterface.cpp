#include "appactionInterface.h"
#include "windowInterface.h"
#include "tools/log.hpp"

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

        m_mainWindow = nullptr;

        if( sm_appaction )
        {
            return true;
        }

        if( object::init() )
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
        onAppactionStart();

        m_appactionTime = glfwGetTime();

        m_appactionRunning = true;

        //如果没有创建任何窗口 程序结束
        if( windowInterface::GetAll().size() <= 0 )
        {
            m_appactionRunning = false;
        }
        
        while( m_appactionRunning )
        {
            onTick( glfwGetTime() - m_appactionTime );
            m_appactionTime = glfwGetTime();
            onDraw();

            if( windowInterface::GetAll().size() > 0 )
            {
                glfwPollEvents();
            }
            IMGCMake
        }

        onAppactionFinish();
        glfwTerminate();
        return false;
    }

    bool appactionInterface::destroy(void)
    {
        LOG.info("appactionInterface destroy");

        return object::destroy();
    }

    void appactionInterface::onTick( double p_dt )
    {
        for( basicsInterface * item : windowInterface::GetAll() )
        {
            item->onTick( p_dt );
        }
    }
    void appactionInterface::onDraw( void )
    {
        for( basicsInterface * item : windowInterface::GetAll() )
        {
            item->onDraw();
        }
    }
}