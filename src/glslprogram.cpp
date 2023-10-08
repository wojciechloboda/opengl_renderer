#include "glslprogram.h"
#include <vector>
    
GLSLProgram::GLSLProgram()
{
    programId = glCreateProgram();
    if(glGetError() != 0)
    {
        fprintf(stderr,"Error creating a program\n");
    }
}

void GLSLProgram::attachVertexShader(const char* path)
{
    vertexShader = std::make_unique<Shader>(path, GL_VERTEX_SHADER);
    glAttachShader(programId, vertexShader->shaderId);
    if(glGetError() != 0)
    {
        fprintf(stderr, "Error attaching a shader to a program\n");
    }
}

void GLSLProgram::attachFragmentShader(const char* path)
{
    fragmentShader = std::make_unique<Shader>(path, GL_FRAGMENT_SHADER);
    glAttachShader(programId, fragmentShader->shaderId);
    if(glGetError() != 0)
    {
        fprintf(stderr, "Error attaching a shader to a program\n");
    }
}

void GLSLProgram::linkProgram()
{
    glLinkProgram(programId);
    if(glGetError() != 0)
    {
        fprintf(stderr, "Error linking a program\n");
    }
}

void GLSLProgram::setUniform(const char* name, glm::mat4 matrix)
{
    GLuint location = glGetUniformLocation(programId, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    if(glGetError() != 0)
    {
        fprintf(stderr, "Error setting uniform\n");
    }
}

void GLSLProgram::setUniform(const char* name, glm::vec3 vector)
{
    GLuint location = glGetUniformLocation(programId, name);
    glUniform3fv(location, 1, glm::value_ptr(vector));
    if(glGetError() != 0)
    {
        fprintf(stderr, "Error setting uniform\n");
    }
}

void GLSLProgram::setUniform(const char* name, float val)
{
    GLuint location = glGetUniformLocation(programId, name);
    glUniform1fv(location, 1, &val);
    if(glGetError() != 0)
    {
        fprintf(stderr, "Error setting uniform\n");
    }
}

void GLSLProgram::useProgram()
{
    glUseProgram(programId);
}

GLSLProgram::~GLSLProgram()
{
    glDeleteProgram(programId);
}