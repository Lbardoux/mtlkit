/**
 * @file GlCore.hpp
 * @brief Thanks to Jean-Claude Iehl for this piece of code.
 */
#ifndef _GK_GL3CORE_H
    #ifdef GK_MACOS
        #include <OpenGL/gl3.h>
        #define NO_GLEW
    #else
        #define GLEW_NO_GLU
        #include "GL/glew.h"
    #endif
#endif
#include <GL/gl.h>
