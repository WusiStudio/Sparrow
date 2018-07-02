#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shaderProgramGLSL.h"

namespace ROOT_NAMESPACE
{
    shaderProgramGLSL & shaderProgramGLSL::Create( shaderGLSL & p_vertex, shaderGLSL & p_fragment )
    {
        shaderProgramGLSL & t_result = Create();

        bool t_initResult = t_result.initWidthShader( p_vertex, p_fragment );
        assert( !t_initResult );

        return t_result;
    }


    shaderProgramGLSL & shaderProgramGLSL::Create( const std::string & p_vertexName, const std::string & p_fragmentName )
    {
        shaderProgramGLSL & t_result = Create();

        bool t_initResult = t_result.initWidthShaderName( p_vertexName, p_fragmentName );
        assert( !t_initResult );

        return t_result;
    }


    bool shaderProgramGLSL::init( void )
    {
        if( object::init() )
        {
            return true;
        }

        return false;
    }

    bool shaderProgramGLSL::initWidthShader( shaderGLSL & p_vertex, shaderGLSL & p_fragment )
    {

        m_shaderProgramId = glCreateProgram();
        if( glIsProgram(m_shaderProgramId) != GL_TRUE )
        { 
            return true; 
        }

        m_shaderList.push_back( &p_vertex );
        m_shaderList.push_back( &p_fragment );
        
        for( shaderGLSL * item : m_shaderList )
        {
            if( attchShader( *item ) )
            {
                return true;
            }
        }

        if( linkProgram() )
        {
            return true;
        }

        return false;
    }

    bool shaderProgramGLSL::initWidthShaderName( const std::string & p_vertexName, const std::string & p_fragmentName )
    {
        shaderGLSL & t_vertex = shaderGLSL::Create( p_vertexName );
        shaderGLSL & t_fragment = shaderGLSL::Create( p_fragmentName );

        return initWidthShader( t_vertex, t_fragment );
    }

    void shaderProgramGLSL::use(void) const
    {
        glUseProgram( m_shaderProgramId );
    }

    const bool shaderProgramGLSL::uniformSet( const char * p_uniformName, const int p_data ) const
    {
        GLuint t_uboIndex = getUniformLocation( p_uniformName );
        if( t_uboIndex == GL_INVALID_INDEX ) return true;

        glUniform1i( t_uboIndex, p_data );
        return false;
    }

    const bool shaderProgramGLSL::uniformSet( const char * p_uniformName, const float p_data ) const
    {
        GLuint t_uboIndex = getUniformLocation( p_uniformName );
        if( t_uboIndex == GL_INVALID_INDEX ) return true;

        glUniform1f( t_uboIndex, p_data );
        return false;
    }
    
    const bool shaderProgramGLSL::uniformSet( const char * p_uniformName, const glm::vec2 & p_data ) const
    {
        GLuint t_uboIndex = getUniformLocation( p_uniformName );
        if( t_uboIndex == GL_INVALID_INDEX ) return true;

        glUniform2fv( t_uboIndex, 1, &p_data[0] );
        return false;
    }

    const bool shaderProgramGLSL::uniformSet( const char * p_uniformName, const glm::vec3 & p_data ) const
    {
        GLuint t_uboIndex = getUniformLocation( p_uniformName );
        if( t_uboIndex == GL_INVALID_INDEX ) return true;

        glUniform3fv( t_uboIndex, 1, &p_data[0] );
        return false;
    }

    const bool shaderProgramGLSL::uniformSet( const char * p_uniformName, const glm::vec4 & p_data ) const
    {
        GLuint t_uboIndex = getUniformLocation( p_uniformName );
        if( t_uboIndex == GL_INVALID_INDEX ) return true;

        glUniform4fv( t_uboIndex, 1, &p_data[0] );
        return false;
    }

    const bool shaderProgramGLSL::uniformSet( const char * p_uniformName, const glm::mat4x4 & p_data ) const
    {
        GLuint t_uboIndex = getUniformLocation( p_uniformName );
        if( t_uboIndex == GL_INVALID_INDEX ) return true;

        glUniformMatrix4fv( t_uboIndex, 1, false, &p_data[0][0] );
        return false;
    }

    bool shaderProgramGLSL::destroy( void )
    {

        for( shaderGLSL * item : m_shaderList )
        {
            if( attchShader( *item ) )
            {
                return true;
            }
        }

        m_shaderList.clear();

        if( glIsProgram(m_shaderProgramId) == GL_TRUE )
        {
            glDeleteProgram( m_shaderProgramId );
            m_shaderProgramId = 0;
        }

        return false;
    }

    const bool shaderProgramGLSL::attchShader( shaderGLSL & p_shader )
    {
        const unsigned int shaderId = p_shader.shaderId();
        
        if( !shaderId )
        {
            LOG.error( "# shaderProgramGLSL::attachShader #  Shader Is Not legitimate!" );
            return true;
        }
        p_shader.retain();
        glAttachShader( m_shaderProgramId, shaderId );
        return false;
    }

    const bool shaderProgramGLSL::detachShader( shaderGLSL & p_shader )
    {
        const unsigned int shaderId = p_shader.shaderId();
        if( !shaderId )
        {
            LOG.error( "# shaderProgramGLSL::detachShader #  Shader Is Not legitimate!" );
            return true;
        }
        p_shader.release();
        glDetachShader( m_shaderProgramId, shaderId );
        return false;
    }

    const bool shaderProgramGLSL::linkProgram( void )
    {
        glLinkProgram( m_shaderProgramId );

        GLint linked;
        glGetProgramiv( m_shaderProgramId, GL_LINK_STATUS, &linked );
        if( linked != GL_TRUE )
        { 
            GLint info_len = 0;
            glGetProgramiv( m_shaderProgramId, GL_INFO_LOG_LENGTH, &info_len );
            if( !info_len )
            { 
                LOG.error("# shaderProgramGLSL::linkProgram #  Not Fined Error Info"); 
            }

            GLchar * buff = new GLchar[info_len];
            glGetProgramInfoLog( m_shaderProgramId, info_len, nullptr, buff );
            LOG.error( "# shaderProgramGLSL::linkProgram #  {0}", buff );
            delete [] buff;

            return true;
        }

        for( shaderGLSL * item : m_shaderList )
        {
            if( attchShader( *item ) )
            {
                return true;
            }
        }

        m_shaderList.clear();

        return false;
    }

    GLuint shaderProgramGLSL::getUniformLocation( const char * name ) const 
    {
        
        GLuint t_uboIndex = GL_INVALID_INDEX;
        
        t_uboIndex = glGetUniformLocation( m_shaderProgramId, name );
        if( t_uboIndex == GL_INVALID_INDEX )
        {
            LOG.error( "unifrom name is invalid" );
            return t_uboIndex;
        }

        return t_uboIndex;
    }


    const unsigned short shaderProgramGLSL::TypeSize(const GLenum type)
    {
        unsigned short result;
        #define CASE(Enum, Count, Type) case Enum : result = Count * sizeof(Type); break;

        switch (type) {
            CASE(GL_FLOAT, 1, GLfloat);
            CASE(GL_FLOAT_VEC2, 2, GLfloat);
            CASE(GL_FLOAT_VEC3, 3, GLfloat);
            CASE(GL_FLOAT_VEC4, 4, GLfloat);

            CASE(GL_INT, 1, GLint);
            CASE(GL_INT_VEC2, 2, GLint);
            CASE(GL_INT_VEC3, 3, GLint);
            CASE(GL_INT_VEC4, 4, GLint);

            CASE(GL_UNSIGNED_INT, 1, GLuint);
            CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
            CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
            CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);

            CASE(GL_BOOL, 1, GLboolean);
            CASE(GL_BOOL_VEC2, 1, GLboolean);
            CASE(GL_BOOL_VEC3, 1, GLboolean);
            CASE(GL_BOOL_VEC4, 1, GLboolean);

            CASE(GL_FLOAT_MAT2, 4, GLfloat);
            CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
            CASE(GL_FLOAT_MAT2x4, 8, GLfloat);

            CASE(GL_FLOAT_MAT3, 9, GLfloat);
            CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
            CASE(GL_FLOAT_MAT3x4, 12, GLfloat);

            CASE(GL_FLOAT_MAT4, 16, GLfloat);
            CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
            CASE(GL_FLOAT_MAT4x3, 12, GLfloat);

            #undef CASE

        default:
            result = 0;
            break;

        }

        return result;
    }

}