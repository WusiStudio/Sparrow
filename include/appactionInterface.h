#pragma once
#ifndef __APPACTION_INTERFACE_H__
#define __APPACTION_INTERFACE_H__

#include "imemory/object.hpp"
#include "basicsInterface.h"
#include "glm/glm.hpp"
#include "windowInterface.h"

#include <string>
#include <list>

namespace ROOT_NAMESPACE
{
    class appactionInterface: public basicsInterface
    {
    public:
        static appactionInterface & instance( void );

        virtual void onAppactionStart( void ) = 0;
        virtual void onAppactionFinish( void ) = 0;

        void finish( void );

    protected:
        virtual bool init(void) override;

        virtual bool destroy( void ) override;

        virtual void onTick( double p_dt ) final;
        virtual void onDraw( void ) final;

    private:
        static appactionInterface * sm_appaction;
        double m_appactionTime;
        bool m_appactionRunning;
    };
}

#endif //__APPACTION_INTERFACE_H__