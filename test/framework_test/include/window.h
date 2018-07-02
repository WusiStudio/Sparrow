#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "shaderProgramGLSL.h"
#include "windowInterface.h"

namespace ROOT_NAMESPACE
{
    class window: public windowInterface
    {
    public:
        CREATEFUNC(window);
    protected:
        virtual bool init(void) override;
        

        virtual void onTick( double p_dt ) override;
        virtual void onDraw( void ) override;
    private:
        shaderProgramGLSL * m_shaderProgram;
        GLuint m_vao, m_vbo, m_ebo;
    };
}


#endif //__WINDOW_H__