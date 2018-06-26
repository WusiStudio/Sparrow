#pragma once
#ifndef __SHADER_GLSL_H__
#define __SHADER_GLSL_H__

#include "imemory/object.hpp"

// #include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace ROOT_NAMESPACE
{

    enum ShaderType{
        vertex = GL_VERTEX_SHADER,
        fragment = GL_FRAGMENT_SHADER
    };

    class shaderGLSL : public object
    {
    public:
        static shaderGLSL & Create( const ShaderType p_shaderType, const char * p_shaderSource );
    protected:

        CREATEFUNC(shaderGLSL);

        virtual bool init( void ) override;
        virtual bool initWitchSource( const ShaderType p_shaderType, const char * p_shaderSource );

        virtual bool destroy( void ) override;

    private:
        unsigned int m_shaderId;
        ShaderType m_shaderType;

    public:
        unsigned int shaderId( void ) const;

    };
}

#endif //__SHADER_GLSL_H__