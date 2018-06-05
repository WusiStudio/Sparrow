#pragma once
#ifndef __APPACTION_INTERFACE_H__
#define __APPACTION_INTERFACE_H__

#include "imemory/object.hpp"
#include "basicsInterface.h"
#include "glm/glm.hpp"
#include "window.h"

#include <string>
#include <list>

namespace ROOT_NAMESPACE
{
    class appactionInterface: public basicsInterface
    {
    public:
        static appactionInterface instance( void );

        virtual void onAppactionStart( void ) = 0;
        virtual void onAppactionFinish( void ) = 0;

    protected:
        virtual bool init(void) override;

        CREATEFUNC(appactionInterface);
        ~appactionInterface(void);

        virtual void onTick( double p_dt ) override;
        virtual void onDraw( void ) override;

    private:
        static appactionInterface * sm_appaction;
        double m_appactionTime;
        bool m_appactionRunning;
    };
}

#endif //__APPACTION_INTERFACE_H__