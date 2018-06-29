#include "shaderGLSL.h"
#include "tools/log.hpp"
#include "appactionInterface.h"
#include "file.h"

namespace ROOT_NAMESPACE
{
    shaderGLSL & shaderGLSL::Create( const ShaderType p_shaderType, const char * p_shaderSource )
    {
        shaderGLSL & t_result = Create();

        bool t_initResult = t_result.initWithSource( p_shaderType, p_shaderSource );

        assert( !t_initResult );

        return t_result;
    }

    shaderGLSL & shaderGLSL::Create( const std::string & p_fileName )
    {
        shaderGLSL & t_result = Create();

        bool t_initResult = t_result.initWithFileName( p_fileName );

        assert( !t_initResult );

        return t_result;
    }

    shaderGLSL & shaderGLSL::Create( const std::string & p_fileName, const ShaderType p_shaderType )
    {
        shaderGLSL & t_result = Create();

        bool t_initResult = t_result.initWithFileNameType( p_fileName, p_shaderType );

        assert( !t_initResult );

        return t_result;
    }

    std::string & shaderGLSL::shaderPath( void )
    {
        static std::string s_shaderPath = appactionInterface::instance().assetsPath() + "shader" + PATH_SPACE;
        return s_shaderPath;
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

    bool shaderGLSL::initWithSource( const ShaderType p_shaderType, const char * p_shaderSource )
    {
        m_shaderType = p_shaderType;
        m_shaderId = glCreateShader( m_shaderType );


        

        if( glIsShader( m_shaderId ) != GL_TRUE )
        {
            LOG.info( "----------", GL_VERTEX_SHADER );
            LOG.info( "----------", m_shaderType ); 
            return true; 
        }

        const GLchar * t_source = p_shaderSource;
        glShaderSource( m_shaderId, 1, &t_source, nullptr );

        glCompileShader( m_shaderId );

        GLint compiled = 0;
        glGetShaderiv( m_shaderId, GL_COMPILE_STATUS, &compiled );
        if( compiled != GL_TRUE )
        { 
            GLint infoLen = 0;
            glGetShaderiv( m_shaderId, GL_INFO_LOG_LENGTH, &infoLen );

            if( infoLen == 0 )
            {
                LOG.error( "# Shader::compile #  Not Fined Error Info" );
                return true;
            }

            GLchar * buff = new GLchar[infoLen];
            glGetShaderInfoLog( m_shaderId, infoLen, nullptr, buff );

            LOG.error( "# Shader::compile #  {0}", buff );
            delete [] buff;
            return true; 
        }

        return false;
    }

    bool shaderGLSL::initWithFileName( const std::string & p_fileName )
    {
        std::vector<std::string> t_fileNameSuffix = split( p_fileName, '.' );

        if( t_fileNameSuffix.size() != 2 )
        {
            LOG.error( "shader file named error" );
            return true;
        }

        if( t_fileNameSuffix[1] == "vert" )
        {
            return initWithFileNameType( p_fileName, ShaderType::vertex );
        }else if( t_fileNameSuffix[1] == "frag" )
        {
            return initWithFileNameType( p_fileName, ShaderType::fragment );
        }

        LOG.error( "sahder file suffix name that can not be identified" );

        return true;
    }

    bool shaderGLSL::initWithFileNameType( const std::string & p_fileName, const ShaderType p_shaderType )
    {
        std::string t_fileSource = file::ReadAllText( shaderPath() + p_fileName );

        return initWithSource( p_shaderType, t_fileSource.c_str() );
    }

    bool shaderGLSL::destroy( void )
    {
        if( glIsShader( m_shaderId ) == GL_TRUE )
        {
            glDeleteShader( m_shaderId );
        }

        return false;
    }

    unsigned int shaderGLSL::shaderId( void ) const
    {
        if( glIsShader( m_shaderId ) != GL_TRUE )
        { 
            return m_shaderId; 
        }
        return 0;
    }

}