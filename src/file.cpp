#include "file.h"
#include "tools/log.hpp"
#include "tools/md5.hpp"

#if defined(OS_WINDOWS)
#include <io.h>
#define ACCESS _access
#else
#include <unistd.h>
#define ACCESS access
#endif


namespace ROOT_NAMESPACE
{
    file & file::Create( const std::string & p_filePath, unsigned int p_mode )
    {
        file & t_result = Create();

        bool t_initResult = t_result.initWidthPath( p_filePath, p_mode );

        assert( !t_initResult );

        return t_result;
    }

    bool file::PathIsExist( const std::string & p_filePath )
    {
        return ACCESS(p_filePath.c_str(), 0) != -1;
    }

    std::vector<char> file::ReadAll(const std::string & p_filePath)
    {
        file & t_file = Create( p_filePath, std::fstream::in | std::ios::binary );

        return t_file.readAll();
    }

    std::string file::ReadAllText( const std::string & p_filePath )
    {
        const std::vector< char > & binaryContent = ReadAll( p_filePath );
        return std::string( binaryContent.begin(), binaryContent.end() );
    }

    std::string file::MD5( const std::string & p_filePath )
    {
        file & t_file = Create( p_filePath, std::fstream::in | std::ios::binary );
        return t_file.getMD5();
    }

    unsigned int file::fileSize( void )
    {
        std::streampos begin, end;
        begin = m_fs.tellg();
        m_fs.seekg( 0, std::ios::end );
        end = m_fs.tellg();

        m_fs.seekg( 0, std::ios::beg );

        return end - begin;
    }


    bool file::init( void )
    {
        if( object::init() )
        {
            return true;
        }

        return false;
    }

    bool file::initWidthPath( const std::string & p_filePath, std::ios_base::openmode p_mode )
    {

        if( !PathIsExist( p_filePath ) )
        {
            LOG.error( "path \"{0}\" not exist", p_filePath );
            return true;
        }

        m_fs.open( p_filePath, p_mode);

        if( m_fs.fail() )
        {
            return true;
        }

        return false;
    }

    bool file::destroy( void )
    {
        if( m_fs.is_open() )
        {
            LOG.info( "file destroy" );
            m_fs.close();
        }

        return false;
    }

    std::vector<char> file::readAll( void )
    {
        unsigned int t_fileSize = fileSize();
        std::vector<char> t_result( (size_t)t_fileSize );
        m_fs.seekg( 0, std::ios::beg );
        m_fs.read( &t_result[0], t_fileSize );
        m_fs.seekg( 0, std::ios::beg );
        return t_result;
    }

    std::string file::readAllText( void )
    {
        const std::vector< char > & binaryContent = readAll( );
        return std::string( binaryContent.begin(), binaryContent.end() );
    }

    std::string file::getMD5( void )
    {
        return md5( readAllText() ).digest();
    }
}