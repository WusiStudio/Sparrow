#pragma once
#ifndef __WINDOW_INTERFACE_H__
#define __WINDOW_INTERFACE_H__

#include "imemory/object.hpp"
#include "basicsInterface.h"
#include "GLFW/glfw3.h"
#include <list>
#include <string>
#include "glm/glm.hpp"

namespace ROOT_NAMESPACE
{
    class windowInterface: public basicsInterface
    {
    public:
        static const std::list<windowInterface *> GetAll();
        static bool isExist( windowInterface * p_window );
    protected:

        virtual bool initWindow( const std::string & p_name, const glm::ivec2 & p_size, const glm::ivec2 & p_position = glm::ivec2(0) );
        virtual bool init(void) override;

        virtual void onTick( double p_dt ) override;
        virtual void onDraw( void ) override = 0;

        virtual bool destroy( void ) override;

    private:
        GLFWwindow * m_glfwWindow;
        static std::list<windowInterface *> sm_windowList;

        int m_fps;
        time_t m_prveTime;
    };
}

#endif //__WINDOW_INTERFACE_H__
