#include "windowInterface.h"
#include "appactionInterface.h"

namespace ROOT_NAMESPACE
{
    std::list<windowInterface *> windowInterface::sm_windowList;

    const std::list<windowInterface *> windowInterface::GetAll()
    {
        return sm_windowList;
    }

    bool windowInterface::initWindow( const std::string & p_name, const glm::ivec2 & p_size, const glm::ivec2 & p_position )
    {
        if( object::init() )
        {
            return true;
        }

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
        if( glfwWindowShouldClose(m_glfwWindow) )
        {
            sm_windowList.remove( this );

            release();

            glfwDestroyWindow(m_glfwWindow);
            m_glfwWindow = nullptr;

            // 窗口关闭 退出app
            if( sm_windowList.size() <= 0 )
            {
                appactionInterface::instance().finish();
            }
        }

        IMGCMake
    }

    bool windowInterface::destroy()
    {
        LOG.info("windowInterface destroy");
        return object::destroy();
    }
}