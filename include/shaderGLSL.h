#pragma once
#ifndef __SHADER_GLSL_H__
#define __SHADER_GLSL_H__

#include "GLFW/glfw3.h"

#include "imemory/object.hpp"

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
        static shaderGLSL & Create( const std::string & p_fileName );
        static shaderGLSL & Create( const std::string & p_fileName, const ShaderType p_shaderType );
        
        static std::string & shaderPath( void );
    protected:

        CREATEFUNC(shaderGLSL);

        virtual bool init( void ) override;
        virtual bool initWithSource( const ShaderType p_shaderType, const char * p_shaderSource );
        virtual bool initWithFileName( const std::string & p_fileName );
        virtual bool initWithFileNameType( const std::string & p_fileName, const ShaderType p_shaderType );

        virtual bool destroy( void ) override;

    private:
        unsigned int m_shaderId;
        ShaderType m_shaderType;

    public:
        unsigned int shaderId( void ) const;

    };
}

#endif //__SHADER_GLSL_H__