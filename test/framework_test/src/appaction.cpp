#include "appaction.h"
#include "window.h"


namespace ROOT_NAMESPACE
{

    appaction & appaction::Create( int p_argc, char ** p_argv )
    {
        appaction & t_result = Create();

        bool t_initWidthParameterResult = t_result.initWithParameter( p_argc, p_argv );

        assert( !t_initWidthParameterResult );

        return t_result;
    }
    

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
    }
    void appaction::onAppactionFinish( void )
    {
        
    }
}