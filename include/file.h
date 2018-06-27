#pragma once
#ifndef __FILE_H__
#define __FILE_H__

#include "imemory/object.hpp"
#include <string>
#include <fstream>
#include <vector>

namespace ROOT_NAMESPACE
{
    class file : public object
    {
    public:
        static file & Create( const std::string & p_filePath, const std::ios_base::openmode p_mode = std::fstream::in | std::fstream::out | std::fstream::app );

        static bool PathIsExist( const std::string & p_filePath );

        static std::vector<char> ReadAll( const std::string & p_filePath );

        static std::string ReadAllText( const std::string & p_filePath );

        static std::string MD5( const std::string & p_filePath );
    
        unsigned int fileSize( void );

        std::vector<char> readAll( void );
        std::string readAllText( void );
        std::string getMD5( void );
    protected:

        CREATEFUNC( file );

        virtual bool init( void ) override;
        virtual bool initWidthPath( const std::string & p_filePath, std::ios_base::openmode p_mode );

        virtual bool destroy( void ) override;
        
    private:

        std::fstream m_fs;
    };
}

#endif //__FILE_H__