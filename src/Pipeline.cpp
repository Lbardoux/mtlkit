#include <stdexcept>
#include <map>
#include <string>
#include <algorithm>

#include "Pipeline.hpp"
#include "vec.hpp"
#include "XmlLoader.hpp"

namespace // Getting a GLenum
{
	GLenum getGLenum(GLenum parameter) noexcept
	{
		GLenum value = GL_NONE;
		glGetIntegerv(parameter, reinterpret_cast<GLint*>(&value));
		return value;
	}
	
	std::map<std::string, GLenum> depth_functions = {
		{"less",          GL_LESS},
		{"equal",         GL_EQUAL},
		{"less_equal",    GL_LEQUAL},
		{"never",         GL_NEVER},
		{"greater",       GL_GREATER},
		{"not_equal",     GL_NOTEQUAL},
		{"greater_equal", GL_GEQUAL},
		{"always",        GL_ALWAYS}
	};
	
	std::map<std::string, GLenum> cullface_functions = {
		{"front",      GL_FRONT},
		{"back",       GL_BACK},
		{"front_back", GL_FRONT_AND_BACK}
	};
	
	GLenum getDepthFunction(const std::string& xmlParam)
	{
		auto element = depth_functions.find(xmlParam);
		if (element != depth_functions.end())
		{
			return element->second;
		}
		throw std::runtime_error("Invalid depthFunction value !");
	}
	
	void enableDisable(GLenum parameter, GLboolean boolean)
	{
		if (boolean)
		{
			glEnable(parameter);
			return;
		}
		glDisable(parameter);
	}
	
	GLenum getCullFaceRotation(const std::string& rotation)
	{
		return (rotation == "clockwise") ? GL_CW : GL_CCW;
	}
	
	GLenum getCullFace(const std::string& cullface)
	{
		auto it = cullface_functions.find(cullface);
		if (it != cullface_functions.end())
		{
			return it->second;
		}
		return GL_FRONT;
	}
	
}


GLenum Pipeline::depthTestFunction(void) noexcept
{
	return getGLenum(GL_DEPTH_FUNC);
}

void Pipeline::depthTestFunction(GLenum function)
{
	if (is_valid_depth_function_enum(function))
	{
		glDepthFunc(function);
		return;
	}
	throw std::invalid_argument("Bad enum value for depthTestFunction !");
}

GLboolean Pipeline::depthTest(void) noexcept
{
	GLboolean value;
	glGetBooleanv(GL_DEPTH_TEST, &value);
	return value;
}

void Pipeline::depthTest(bool enable) noexcept
{
	enableDisable(GL_DEPTH_TEST, enable);
}

GLfloat Pipeline::depthClearValue(void) noexcept
{
	GLfloat value;
	glGetFloatv(GL_DEPTH_CLEAR_VALUE, &value);
	return value;
}

void Pipeline::depthClearValue(GLfloat value) noexcept
{
	glClearDepthf(value);
}

Color Pipeline::clearColor(void) noexcept
{
	Color result;
	glGetFloatv(GL_COLOR_CLEAR_VALUE, result);
	return result;
}

void Pipeline::clearColor(const Color& color) noexcept
{
	glClearColor(color.r(), color.g(), color.b(), color.a());
}

void Pipeline::clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept
{
	glClearColor(r, g, b, a);
}

GLboolean Pipeline::culling(void) noexcept
{
	GLboolean value;
	glGetBooleanv(GL_CULL_FACE, &value);
	return value;
}

void Pipeline::culling(GLboolean enable) noexcept
{
	enableDisable(GL_CULL_FACE, enable);
}

void Pipeline::rotationDirection(GLenum direction)
{
	if (direction != GL_CW && direction != GL_CCW)
	{
		throw std::runtime_error("Invalid rotation value for glFrontFace !");
	}
	glFrontFace(direction);
}

GLenum Pipeline::rotationDirection(void) noexcept
{
	return getGLenum(GL_FRONT_FACE);
}

void Pipeline::cullFace(GLenum type)
{
	for (auto it : cullface_functions)
	{
		if (it.second == type)
		{
			glCullFace(type);
			return;
		}
	}
	throw std::runtime_error("Wrong enum for glCullFace !");
}

GLenum Pipeline::cullFace(void) noexcept
{
	return getGLenum(GL_CULL_FACE_MODE);
}

void Pipeline::clear(bool depth, bool color, bool accum, bool stencil) noexcept
{
	GLbitfield flags = depth*GL_DEPTH_BUFFER_BIT;
	flags |= color*GL_COLOR_BUFFER_BIT;
	flags |= accum*GL_ACCUM_BUFFER_BIT;
	flags |= stencil*GL_STENCIL_BUFFER_BIT;
	glClear(flags);
}


void Pipeline::fromXML(const GLchar* fname)
{
	XmlLoader loader(fname);
	Pipeline::depthTest(loader.node("depth").element("enableDepthTest").text<bool>());
	Pipeline::depthTestFunction(getDepthFunction(loader.element("depthFunction").text<std::string>()));
	Pipeline::depthClearValue(loader.element("clearDepthValue_f").text<float>());
	loader.prev();
	
	Color color;
	color.r(loader.node("clearColor").element("red_f").text<float>());
	color.g(loader.element("green_f").text<float>());
	color.b(loader.element("blue_f").text<float>());
	color.a(loader.element("alpha_f").text<float>());
	Pipeline::clearColor(color);
	loader.prev();
	
	Pipeline::culling(loader.node("cullFace").element("enableCulling").text<bool>());
	Pipeline::rotationDirection(getCullFaceRotation(loader.element("rotationDirection").text<std::string>()));
	Pipeline::cullFace(getCullFace(loader.element("keeping").text<std::string>()));
	loader.prev();
}
