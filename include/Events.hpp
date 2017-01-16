/**
 * @file Events.hpp
 * @brief Offers some functions to catch some user's events (like keyboard, mouse).
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_EVENTS_HPP_INCLUDED
#define MTLKIT_EVENTS_HPP_INCLUDED

#include <SDL2/SDL.h>


class GlContext;

/**
 * @class EventManager
 * @brief Handles events from keyboard, window, and mouse.
 * You could easily access to them with static public members/
 */
class EventManager final
{
	public:
		/**
		 * @brief Read every possible events at this moment and fill internals variables
		 * @return true if you have to quit the program, false otherwise
		 */
		static bool catchEvents(void);
		/**
		 * @brief Checks if the physical key represented by \b character is pressed.
		 * @param[in] character The character of a QWERTY keyboard to check.
		 * @return true if this key is pressed, false otherwise.
		 * @throw std::out_of_range If the requested key gots a too high value.
		 * 
		 * @code
		 * // Check if Q of the qwerty keyboard is pressed.
		 * EventManager::keyPressed('q');
		 * // That means the A for an azerty keyboard.
		 * @endcode
		 */
		static bool keyPressed(char character);
		/**
		 * @brief Checks if the physical key represented by \b character is released.
		 * @param[in] character The character of a QWERTY keyboard to check.
		 * @return true if this key is released, false otherwise.
		 * @throw std::out_of_range If the requested key gots a too high value.
		 * 
		 * @code
		 * // Check if Q of the qwerty keyboard is released.
		 * EventManager::keyReleased('q');
		 * // That means the A for an azerty keyboard.
		 * @endcode
		 */
		static bool keyReleased(char character);
		
		
		
	private:
		static SDL_Event event;  //!< The variable which will catch events from SDL.
		friend class GlContext;
		//! @brief Initialize everything for the event part.
		static void init(void);
		
		EventManager(void) = delete;
};



#endif
