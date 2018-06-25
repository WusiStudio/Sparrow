#include "shaderGLSL.h"
#include "tools/log.hpp"

namespace ROOT_NAMESPACE
{
    shaderGLSL & shaderGLSL::Create( const ShaderType p_shaderType, const char * p_shaderSource )
    {
        shaderGLSL & t_result = Create();

        assert( !t_result.initWitchSource( p_shaderType, p_shaderSource ) );

        return t_result;
    }

    bool shaderGLSL::init( void )
    {
        if( object::init() )
        {
            return true;
        }

        m_shaderId = 0;

        return false;
    }

    bool shaderGLSL::initWitchSource( const ShaderType p_shaderType, const char * p_shaderSource )
    {
        m_shaderType = p_shaderType;
        m_shaderId = glCreateShader( m_shaderType );

        if( glIsShader(m_shaderId) != GL_TRUE ){ return true; }

        const GLchar * t_source = p_shaderSource;
        glShaderSource(m_shaderId, 1, &t_source, nullptr);

        glCompileShader(m_shaderId);

        GLint compiled = 0;
        glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compiled);
        if( compiled == GL_TRUE ){ return false; }

        GLint infoLen = 0;
        glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen == 0)
        {
            LOG.error("# Shader::compile #  Not Fined Error Info");
            return true;
        }

        GLchar * buff = new GLchar[infoLen];
        glGetShaderInfoLog(m_shaderId, infoLen, nullptr, buff);

        LOG.error("# Shader::compile #  {0}", buff);
        delete [] buff;

        return true;
    }

    unsigned int shaderId( void )
    {
        if( glIsShader( m_shaderId ) != GL_TRUE )
        { 
            return m_shaderId; 
        }
        return 0;
    }
}