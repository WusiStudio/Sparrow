#pragma once
#ifndef __SHADER_PROGRAM_GLSL_H__
#define __SHADER_PROGRAM_GLSL_H__

#include "imemory/object.hpp"
#include "glad/glad.h"
#include "shaderGLSL.h"
#include <list>
#include "glm/glm.hpp"

namespace ROOT_NAMESPACE
{
    class shaderProgramGLSL : public object
    {
    public:
        static shaderProgramGLSL & Create( shaderGLSL & p_vertex, shaderGLSL & p_fragmaent );

        shaderGLSL * getShader( const ShaderType p_type ) const;
        void use(void) const;

        const bool uniformSet( const char * p_uniformName, const int p_data ) const;
        const bool uniformSet( const char * p_uniformName, const float p_data ) const;
        
        const bool uniformSet( const char * p_uniformName, const glm::vec2 & p_data ) const;
        const bool uniformSet( const char * p_uniformName, const glm::vec3 & p_data ) const;
        const bool uniformSet( const char * p_uniformName, const glm::vec4 & p_data ) const;

        const bool uniformSet( const char * p_uniformName, const glm::mat4x4 & p_data ) const;

        static const unsigned short TypeSize(const GLenum type);

    protected:
        CREATEFUNC( shaderProgramGLSL );

        virtual bool init( void ) override;

        virtual bool initWidthShader( shaderGLSL & p_vertex, shaderGLSL & p_fragmaent );

        virtual bool destroy( void ) override;
    private:

        const bool attchShader( shaderGLSL & p_shader );
        const bool detachShader( shaderGLSL & p_shader );

        const bool linkProgram( void ) const;

        GLuint getUniformLocation( const char * name ) const;

        unsigned int m_shaderProgramId;
        std::list< shaderGLSL * > m_shaderList;
    };
}


#endif //__SHADER_PROGRAM_GLSL_H__