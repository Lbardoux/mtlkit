/**
 * @file keymap.hpp
 * @brief Maps the keyboard scan codes to an enum.
 * @author MTLCRBN
 */
#ifndef MTLKIT_KEYMAP_HPP_INCLUDED
#define MTLKIT_KEYMAP_HPP_INCLUDED

#include <SDL2/SDL.h>

/**
 * @def KEY 
 * @brief Construct a SDL_SCANCODE for you.
 * @pre \b uppercase must match :
 *    - 0 -> 9
 *    - A -> Z
 *    - DOWN, RIGHT, LEFT, UP
 *    - CANCEL, BACKSPACE, CAPSLOCK, DELETE
 *    - END, EQUAL, 
 *    - 
 *    - 
 * 
 */
#define KEY(uppercase) SDL_SCANCODE_##uppercase

#endif

