#include <stdexcept>
#include <string>
#include <cstdlib>
#include <cstdint>

#include "GlCore.hpp"
#include "GlContext.hpp"
#include "Events.hpp"


GlContext::Window* GlContext::WINDOW = nullptr;
GlContext::Context GlContext::CONTEXT;


GlContext::Window* GlContext::window(void)
{
	return GlContext::WINDOW;
}

GlContext::Context* GlContext::context(void)
{
	return &GlContext::CONTEXT;
}

int32_t GlContext::windowWidth(void) noexcept
{
	int32_t width;
	SDL_GetWindowSize(GlContext::WINDOW, &width, nullptr);
	return width;
}

int32_t GlContext::windowHeight(void) noexcept
{
	int32_t height;
	SDL_GetWindowSize(GlContext::WINDOW, nullptr, &height);
	return height;
}

void GlContext::windowCaption(const char *const title) noexcept
{
	if (title == nullptr)
	{
		return;
	}
	SDL_SetWindowTitle(GlContext::WINDOW, title);
}

namespace // Initialization
{
	const uint32_t SDL_INIT_FLAGS = SDL_INIT_VIDEO;
	void initSDL(void)
	{
		if (SDL_Init(SDL_INIT_FLAGS) < 0)
		{
			throw std::runtime_error(std::string("Failed to init SDL : ") + std::string(SDL_GetError()));
		}
	}
	
	
	const uint32_t SDL_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	#define WINDOW_POS(w, h) SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h
	void initWindow(GlContext::Window** window, int32_t width, int32_t height)
	{
		*window = SDL_CreateWindow("Unamed window",
								   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								   width, height,
								   SDL_FLAGS);
		if (*window == nullptr)
		{
			throw std::runtime_error("Failed to create the window");
		}
		SDL_SetWindowDisplayMode(*window, nullptr);
	}
	
	void initContext(GlContext::Window* window, GlContext::Context& context, int32_t minorVersion, int32_t majorVersion)
	{
		// Credits to Jean Claude Iehl from Universite Lyon 1 for this code.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
		#ifndef GK_RELEASE
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		#endif
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,           16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,         1);
		context = SDL_GL_CreateContext(window);
		if (context == 0)
		{
			throw std::runtime_error(std::string("Failed to create a context : ") + std::string(SDL_GetError()));
		}
		SDL_GL_SetSwapInterval(1);
	}
	
	void initGLEW(GlContext::Context& context)
	{
		// Credits to Jean Claude Iehl from Universite Lyon 1 for this code.
		#ifndef NO_GLEW
			glewExperimental = 1;
			GLenum err = glewInit();
			if(err != GLEW_OK)
			{
				SDL_GL_DeleteContext(context);
				throw std::runtime_error("Failed to initialize GLEW !");
			}
			while(glGetError() != GL_NO_ERROR)
			{
				
			}
		#endif
	}
}

void GlContext::initGL(int32_t width, int32_t height, int32_t minorVersion, int32_t majorVersion)
{
	initSDL();
	initWindow(&GlContext::WINDOW, width, height);
	initContext(GlContext::WINDOW, GlContext::CONTEXT, minorVersion, majorVersion);
	initGLEW(GlContext::CONTEXT);
	EventManager::init();
}

namespace // clean at the end, after destructors.
{
	void _quit_after_destructors(void)
	{
		SDL_GL_DeleteContext(*GlContext::context());
		SDL_DestroyWindow(GlContext::window());
		SDL_Quit();
	}
}

void GlContext::endGL(void)
{
	atexit(_quit_after_destructors);
}
