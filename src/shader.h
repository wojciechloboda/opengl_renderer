#pragma once

#include "glad/glad.h"
#include <vector>
#include <fstream>

class Shader
{
public:
    GLuint shaderId;

    Shader(const char* path, GLenum shaderType)
    {
        std::string source_code_string;
        std::ifstream source_file(path);
        if (!source_file.is_open())
        {
            fprintf(stderr, "Error opening a source file\n");
        }
        source_code_string.assign((std::istreambuf_iterator<char>(source_file)), 
            std::istreambuf_iterator<char>());
        source_file.close();


        if((shaderId = glCreateShader(shaderType)) == 0)
        {
            fprintf(stderr, "Error creating a shader\n");
        }
        
        const char *c_str = source_code_string.c_str();
        glShaderSource(shaderId, 1, &c_str, NULL);
        if(glGetError() != 0)
        {
            fprintf(stderr, "Error adding source to shader\n");
        }

        glCompileShader(shaderId);
        if(glGetError() != 0)
        {
            compileStatus(shaderId);
        }
    }

    GLuint getShaderId()
    {
        return shaderId;
    }

    ~Shader()
    {
        glDeleteShader(shaderId);
    }

    bool compileStatus( GLuint shader )
    {
        GLint status = GL_TRUE;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
        if (status == GL_FALSE)
        {
            GLint logLen;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
            std::vector< char >log( logLen );
            GLsizei written;
            glGetShaderInfoLog( shader, logLen, &written, log.data() );
            fprintf(stderr, "compile error\n");
            fprintf(stderr, log.data());
        }
        return status != GL_FALSE;
    }

private:
};