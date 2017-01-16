/**
 * @file GlContext.hpp
 * @brief Create and prepare a context for OpenGL using SDL2
 * 
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_GLCONTEXT_HPP_INCLUDED
#define MTLKIT_GLCONTEXT_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <cstdint>


class GlContext final
{
    public:
        typedef SDL_Window    Window;  //!< If the user want to mess with that.
        typedef SDL_GLContext Context; //!< same here.
        
        /**
         * @brief Grants access to the address of the OpenGL window.
         * @return An address to this window, you'll not have to delete it.
         */
        static Window* window(void);
        /**
         * @brief Grants access to the address of the OpenGL context.
         * @return An address to this context, you'll not have to delete it.
         */
        static Context* context(void);
		/**
		 * @brief Grants access to the width of the window.
		 * @return The current width of the window, in pixels.
		 */
		static int32_t windowWidth(void) noexcept;
		/**
		 * @brief Grants access to the height of the window.
		 * @return The current height of the window, in pixels.
		 */
		static int32_t windowHeight(void) noexcept;
        /**
         * @brief Create and initialize OpenGL with version between \b minorVersion and \b majorVersion.
         * It also create a window of size \b width x \b height.
         * @param[in] width        The width you want for the window.
         * @param[in] height       The height you want for the window.
         * @param[in] minorVersion The minor version number.
         * @param[in] majorVersion The major version number.
         * @throw std::runtime_error If there is any problem while creating the OpenGL context.
         */
        static void initGL(int32_t width, int32_t height, int32_t minorVersion = 2, int32_t majorVersion = 3);
		/**
		 * @brief Clean everything before ending the program.
		 */
		static void endGL(void);
		/**
		 * @brief Sets the title of the window with \b title.
		 * @param[in] title The new title you wanna display.
		 * @pre \b title must not be nullptr or NULL.
		 * @pre init() statement must be called before !
		 * @post Your title appear at the top of the window !
		 */
		static void windowCaption(const char *const title) noexcept;
        
    private:
        static Window* WINDOW;  //!< The window for OpenGL.
        static Context CONTEXT; //!< The OpenGL context.
        
        GlContext(void) = delete;
        
};

#endif
