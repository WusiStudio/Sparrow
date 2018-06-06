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

        if ( !glfwInit() )
        {
            return true;
        }

        sm_appaction = this;
        onAppactionStart();

        m_appactionTime = glfwGetTime();

        m_appactionRunning = true;

        //如果没有创建任何窗口 程序结束
        if( windowInterface::getAll().size() <= 0 )
        {
            m_appactionRunning = false;
        }
        
        while( m_appactionRunning )
        {
            onTick( glfwGetTime() - m_appactionTime );
            m_appactionTime = glfwGetTime();
            onDraw();
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
        for( basicsInterface * item : windowInterface::getAll() )
        {
            item->onTick( p_dt );
        }

        if( windowInterface::getAll().size() > 0 )
        {
            glfwPollEvents();
        }
    }
    void appactionInterface::onDraw( void )
    {
        for( basicsInterface * item : windowInterface::getAll() )
        {
            item->onDraw();
        }
    }
}