#include <cstdint>
#include <utility>
#include <vector>
#include <stdexcept>

#include <iostream>

#include "Events.hpp"
#include "keymap.hpp"


SDL_Event EventManager::event;


namespace
{    
    int32_t keys_size;
    const uint8_t* states = nullptr;
    
    int32_t getState(SDL_Scancode scan)
    {
        if (scan >= keys_size)
        {
            throw std::out_of_range("Requested key is out of bound");
        }
        return static_cast<int32_t>(states[scan]);
    }
    
}


bool EventManager::keyReleased(SDL_Scancode scan)
{
    return !EventManager::keyPressed(scan);
}

bool EventManager::keyPressed(SDL_Scancode scan)
{
    return getState(scan) != 0;
}

void EventManager::init(void)
{
    states = SDL_GetKeyboardState(&keys_size);
}

void EventManager::update(void)
{
    SDL_PumpEvents();
    states = SDL_GetKeyboardState(nullptr);
}

bool EventManager::catchEvents(void)
{
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
    EventManager::update();
    return false;
}
