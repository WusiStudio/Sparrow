#include "appactionInterface.h"
#include "windowInterface.h"

namespace ROOT_NAMESPACE
{

    appactionInterface * appactionInterface::sm_appaction = nullptr;

    bool appactionInterface::init(void)
    {

        if( m_appaction )
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

        m_appaction = this;
        onAppactionStart();

        m_appactionTime = glfwGetTime();

        m_appactionRunning = true;

        //如果没有创建任何窗口 程序结束
        if( windowInterface::getAll().count <= 0 )
        {
            m_appactionRunning = false;
        }
        
        while( m_appactionRunning )
        {
            onTick( glfwGetTime() - m_appactionTime );
            m_appactionTime = glfwGetTime();
            onDraw();
        }

        return false;
    }

    appactionInterface::~appactionInterface(void)
    {
        onAppactionFinish();
    }

    void appactionInterface::onTick( double p_dt )
    {
        for( windowInterface & item : windowInterface::getAll() )
        {
            item.onTick( p_dt );
        }
    }
    void appactionInterface::onDraw( void )
    {
        for( windowInterface & item : windowInterface::getAll() )
        {
            item.onDraw();
        }
    }
}