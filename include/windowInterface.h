#pragma once
#ifndef __WINDOW_INTERFACE_H__
#define __WINDOW_INTERFACE_H__

#include "imemory/object.hpp"
#include "basicsInterface.h"
#include "GLFW/glfw3.h"
#include <list>

namespace ROOT_NAMESPACE
{
    class windowInterface: public basicsInterface
    {
    public:
        static const td::list<windowInterface &> & getAll();
    protected:
        CREATEFUNC(windowInterface);

        virtual void onTick( double p_dt ) override;

        virtual bool init(void) override;
    private:
        GLFWwindow * m_glfwWindow;
        static std::list<windowInterface &> sm_windowList;
    };
}

#endif //__WINDOW_INTERFACE_H__