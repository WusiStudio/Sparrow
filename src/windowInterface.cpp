#include "windowInterface.h"
#include "appactionInterface.h"

namespace ROOT_NAMESPACE
{
    std::list<windowInterface *> windowInterface::sm_windowList;

    const std::list<windowInterface *> windowInterface::getAll()
    {
        return sm_windowList;
    }

    bool windowInterface::init(void)
    {
        if( object::init() )
        {
            return true;
        }

        m_glfwWindow = glfwCreateWindow(640, 480, "window interface", NULL, NULL);
        if (!m_glfwWindow)
        {
            glfwTerminate();
            return true;
        }

        retain();
        sm_windowList.push_back( this );

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