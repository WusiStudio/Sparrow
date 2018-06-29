#include "glad/glad.h"
#include "appactionInterface.h"
#include "windowInterface.h"
#include "tools/log.hpp"
#include <unistd.h>

#define PATH_BUFFER_SIZE 1024

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

    const std::string & appactionInterface::appactionName( void )
    {
        return m_appactionName;
    }

    const std::string & appactionInterface::appactionPath( void )
    {
        return m_appactionPath;
    }

    const std::string & appactionInterface::assetsPath( void )
    {
        static std::string s_assetsPath = m_appactionPath + "assets" + PATH_SPACE;
        return s_assetsPath;
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

        m_appactionName = "";
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
#if defined(OS_WINDOWS)
        m_appactionPath = "";
#else
        m_appactionPath = PATH_SPACE;
#endif

        std::vector<std::string> t_appPathList;

        //解析程序所在路径
        std::string t_appStartPath = p_argv[0];

        std::vector<std::string> t_startPathList = split( t_appStartPath, PATH_SPACE );
        
        m_appactionName = *( t_startPathList.end() - 1 );

        t_startPathList.erase( --t_startPathList.end() );

        //如果通过绝对路径启动
        if( t_appStartPath[0] == PATH_SPACE[0] || t_startPathList[0][t_startPathList[0].size() - 1] == ':' )
        {
            if( pathMerga( t_appPathList, t_startPathList ) )
            {
                return true;
            }

        //相对路径
        }else{
            char t_pathBuffer[PATH_BUFFER_SIZE];
            if( !getcwd( t_pathBuffer, PATH_BUFFER_SIZE ) )
            {
                LOG.error( "getcwd faild" );
                return true;
            }

            std::vector<std::string> t_workPathList = split( t_pathBuffer, PATH_SPACE );
            if( pathMerga( t_appPathList, t_workPathList ) )
            {
                return true;
            }

            if( pathMerga( t_appPathList, t_startPathList ) )
            {
                return true;
            }
        }

        for( std::string & t_dir : t_appPathList )
        {
            m_appactionPath += t_dir + PATH_SPACE;
        }

        return false;
    }

    bool appactionInterface::pathMerga( std::vector< std::string > & p_target, const std::vector< std::string > & p_sub )
    {
        for( int i = 0; i < p_sub.size(); ++i )
        {
            if( p_sub[i].size() == 0 || p_sub[i] == "." )
            {
                continue;
            }
            if( p_sub[i] == ".." && p_target.size() > 0 )
            {
                p_target.erase( --p_target.end() );
                continue;
            }
            p_target.push_back( p_sub[i] );
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