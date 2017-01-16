/**
 * @file Loop.hpp
 * @brief Provides some functions to help writing a render loop code.
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_LOOP_HPP_INCLUDED
#define MTLKIT_LOOP_HPP_INCLUDED

#include "GlCore.hpp"
#include "GlContext.hpp"
#include "Events.hpp"
#include <cstdint>


/**
 * @brief This is the callback function that handles the main render loop process for you.
 * @param[in]     frameRate    The maximal number of frame you want per second.
 * @param[in,out] drawFunction A valid function address.
 * @param[in,out] args         The arguments you wanna pass to this function address when called.
 * @return 0 if everything went well, anything else otherwise
 * @pre \b drawFunction must return \b true in order to stop the loop (so false to continue).
 * @post As long the \b drawFunction doesn't return \b true, call your function and refresh the screen.
 */
template<typename... FunctionArguments>
int32_t renderLoop(uint32_t frameRate, bool (*drawFunction)(FunctionArguments&...), FunctionArguments&... args)
{
	bool     stopLoop = false;
	uint32_t delay    = 1000/frameRate;
	glViewport(0, 0, GlContext::windowWidth(), GlContext::windowHeight());
	
	while(stopLoop != true) 
	{
		stopLoop |= EventManager::catchEvents();
		stopLoop |= drawFunction(args...);
		SDL_GL_SwapWindow(GlContext::window());
		SDL_Delay(delay);
	}
	return 0;
}

#endif

