#include "appaction.h"
#include "window.h"


namespace ROOT_NAMESPACE
{
    bool appaction::init(void)
    {
        if(appactionInterface::init())
        {
            return true;
        }

        return false;
    }

    void appaction::onAppactionStart( void )
    {
        window::Create();
        window::Create();
    }
    void appaction::onAppactionFinish( void )
    {

    }
}