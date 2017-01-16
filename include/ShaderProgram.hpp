/**
 * @file ShaderProgram.hpp
 * @brief This wrapper embeds the main functions for creating and using an OpenGL program.
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_SHADERPROGRAM_HPP_INCLUDED
#define MTLKIT_SHADERPROGRAM_HPP_INCLUDED

#include "GlCore.hpp"
#include <initializer_list> // For std::initializer_list


/**
 * @class ShaderProgram
 * @brief A convenient way to create and manage a shader program for OpenGL.
 * 
 */
class ShaderProgram
{
    public:
        /**
         * @brief Instanciate a single program for OpenGL.
         * @throw std::runtime_error If it cannot configure a single program.
         */
        ShaderProgram(void);
        /**
         * @brief Instanciate a single program and attach every shaders from \b shadersId, then link the program.
         * @param[in] shadersId A list which contains shaders id.
         * @pre \b shadersId must contains only valid shaders id.
         * @post The program is linked with every shaders attached.
         * @throw std::runtime_error if any id is invalid or error for creating the program.
         */
        ShaderProgram(const std::initializer_list<GLuint>& shadersId);
        /**
         * @brief Destroy the program from the openGL context.
         */
        virtual ~ShaderProgram(void) noexcept;
        /**
         * @brief Link the current ShaderProgram.
         * @throw std::runtime_error If any error occurs.
         */
        void link(void);
        /**
         * @brief "Use" this program for the rendering.
         */
        void use(void);
        /**
         * @brief Attach \b shader to the program.
         * @param[in] shader The shader name from OpenGL context.
         * @pre \b shader must be created by OpenGL.
         * @throw std::runtime_error If any error occurs.
         */
        void attach(GLuint shader);
        /**
         * @brief Grants access to the name of this const program.
         * @return This id, different than 0.
         */
        inline GLuint id(void) const noexcept;
        /**
         * @brief Grants access to the name of this program.
         * @return This id, different than 0.
         */
        inline GLuint id(void) noexcept;
        /**
         * @brief Transform this const ShaderProgram into a single GLuint, which is it name from OpenGL context.
         */
        operator GLuint(void) const noexcept;
        /**
         * @brief Transform this ShaderProgram into a single GLuint, which is it name from OpenGL context.
         */
        operator GLuint(void) noexcept;
    
    protected:
        GLuint _id; //!< The name of this program inside OpenGL.
        
};


#endif
