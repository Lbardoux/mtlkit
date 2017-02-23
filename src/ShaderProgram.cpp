/**
 * @file ShaderProgram.cpp
 */
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <functional>
#include <utility>

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
    std::for_each(shadersId.begin(), shadersId.end(), [this](GLuint id){
        this->attach(id);
    });
    this->link();
}

ShaderProgram::~ShaderProgram(void) noexcept
{
    glDeleteProgram(this->_id);
    this->_locations.clear();
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
        std::unique_ptr<char[]> message(new char[length]);
        GLsizei maxLength;
        glGetProgramInfoLog(this->_id, length, &maxLength, message.get());
        std::string fullMessage(message.get());
        message.release();
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

std::vector<GLuint> ShaderProgram::getShaders(void) const noexcept
{
    std::vector<GLuint> result(this->numberOfShaders(), 0);
    GLint count;
    glGetAttachedShaders(*this, result.size(), &count, result.data());
    return result;
}

GLuint ShaderProgram::numberOfShaders(void) const noexcept
{
    GLint value;
    glGetProgramiv(*this, GL_ATTACHED_SHADERS, &value);
    return value;
}

void ShaderProgram::detach(GLuint shader)
{
    if (glIsShader(shader) != GL_TRUE)
    {
        throw std::runtime_error("The given id isn't a shader.");
    }
    glDetachShader(*this, shader);
    if (glGetError() == GL_INVALID_OPERATION)
    {
        throw std::runtime_error("This shader wasn't attached to this program.");
    }
}

bool ShaderProgram::isUniformValid(const std::string& uniformName) const noexcept
{
    return this->uniformLocation(uniformName) != -1;
}

void ShaderProgram::use(void)
{
    glUseProgram(this->_id);
}

bool ShaderProgram::isCurrentlyUsed(void) const noexcept
{
    GLboolean data;
    glGetBooleanv(GL_CURRENT_PROGRAM, &data);
    return data;
}

GLint ShaderProgram::uniformLocation(const std::string& uniformName) const noexcept
{
    std::map<std::string, GLint>::const_iterator iter = this->_locations.find(uniformName);
    if (iter != this->_locations.end())
    {
        return iter->second;
    }
    GLint location = glGetUniformLocation(*this, uniformName.c_str());
    if (location != -1)
    {
        this->_locations.insert(std::make_pair(uniformName, location));
    }
    return location;
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
