#include <cstdint>
#include <utility>
#include <vector>
#include <stdexcept>

#include "Events.hpp"


SDL_Event EventManager::event;


namespace
{
	
	typedef std::pair<char, SDL_Scancode> _Bound;
	struct _Interval final
	{
		_Bound min;
		_Bound max;
		bool match(char value)
		{
			return value >= this->min.first && value <= this->max.first;
		}
		
	};
	std::vector<_Interval> keymap = {
		{{'a', SDL_SCANCODE_A}, {'z', SDL_SCANCODE_Z}},
		{{'A', SDL_SCANCODE_A}, {'Z', SDL_SCANCODE_Z}},
		{{'1', SDL_SCANCODE_1}, {'0', SDL_SCANCODE_0}}
	};
	
	int32_t keys_size;
	const uint8_t *states = nullptr;
	
	int32_t getState(char character)
	{
		for(_Interval& bb : keymap)
		{
			if (bb.match(character))
			{
				uint8_t      offset = character - bb.min.first;
				SDL_Scancode scan   = static_cast<SDL_Scancode>(bb.min.second + offset);
				SDL_Keycode  code   = SDL_GetKeyFromScancode(scan);
				if (code >= keys_size)
				{
					throw std::out_of_range("Requested key is out of bound");
				}
				return (int32_t)states[code];
			}
		}
		return 0;
	}
	
}


bool EventManager::keyReleased(char character)
{
	return !EventManager::keyPressed(character);
}

bool EventManager::keyPressed(char character)
{
	return getState(character) != 0;
}

void EventManager::init(void)
{
	states = SDL_GetKeyboardState(&keys_size);
}

bool EventManager::catchEvents(void)
{
	states = SDL_GetKeyboardState(nullptr);
	while(SDL_PollEvent(&EventManager::event))
	{
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			return true;
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			return true;
		}
	}
	return false;
}
