#pragma once
#ifndef __APPACTION_H__
#define __APPACTION_H__

#include "appactionInterface.h"

namespace ROOT_NAMESPACE
{
    class appaction: public appactionInterface
    {
    public:
        CREATEFUNC(appaction);
    
    protected:
        virtual bool init(void) override;

        virtual void onAppactionStart( void ) override;
        virtual void onAppactionFinish( void ) override;
    private:

    };
}

#endif //__APPACTION_H__