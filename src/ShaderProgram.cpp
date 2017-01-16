#include <stdexcept>
#include <string>

#include "GlCore.hpp"
#include "ShaderProgram.hpp"


ShaderProgram::ShaderProgram(void) : _id(0)
{
    this->_id = glCreateProgram();
    if (this->_id == 0)
    {
        throw std::runtime_error("Cannot create a program for OpenGL !");
    }
}

ShaderProgram::ShaderProgram(const std::initializer_list<GLuint>& shadersId) : ShaderProgram()
{
    for(GLuint id : shadersId)
    {
        this->attach(id);
    }
    this->link();
}

ShaderProgram::~ShaderProgram(void) noexcept
{
    glDeleteProgram(this->_id);
}

void ShaderProgram::link(void)
{
	glLinkProgram(this->_id);
	GLint status;
	glGetProgramiv(this->_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(this->_id, GL_INFO_LOG_LENGTH, &length);
		char*   message = new char[length];
		GLsizei maxLength;
		glGetProgramInfoLog(this->_id, length, &maxLength, message);
		std::string fullMessage(message);
		delete[] message;
		throw std::runtime_error(fullMessage);
	}
}

void ShaderProgram::attach(GLuint shader)
{
	if (glIsShader(shader) != GL_TRUE)
	{
		throw std::runtime_error("The given id isn't a shader.");
	}
    glAttachShader(this->_id, shader);
    if (glGetError() == GL_INVALID_OPERATION)
    {
        throw std::runtime_error("This shader is already attached.");
    }
}

void ShaderProgram::use(void)
{
    glUseProgram(this->_id);
}

GLuint ShaderProgram::id(void) const noexcept
{
    return this->_id;
}

GLuint ShaderProgram::id(void) noexcept
{
    return this->_id;
}

ShaderProgram::operator GLuint(void) const noexcept
{
    return this->_id;
}

ShaderProgram::operator GLuint(void) noexcept
{
    return this->_id;
}
