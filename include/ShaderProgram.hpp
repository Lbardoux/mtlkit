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
#include <map>              // For std::map
#include <string>           // For std::string
#include <vector>           // For std::vector


/**
 * @class ShaderProgram
 * @brief A convenient way to create and manage a shader program for OpenGL.
 * 
 * Right now, it'll offer an uniform locations buffer to accelerate your code.
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
         * @brief Detach @b shader from @b *this.
         * @param[in] shader A valid openGL shader id.
         * @throw std::runtime_error If @b shader isn't attached to @b *this.
         */
        void detach(GLuint shader);
        /**
         * @brief Gets the number of shaders attached to @b *this.
         * @return The number of attached shaders, or 0 if there's none.
         */
        GLuint numberOfShaders(void) const noexcept;
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
        /**
         * @brief Checks if @b uniformName is a valid uniform within this shader program.
         * @details If the requested uniform does exist, it will bufferize it location.
         * @param[in] uniformName The name of an uniform, which one you wanna check.
         * @return true if this uniform name is valid within this program, false otherwise.
         */
        bool isUniformValid(const std::string& uniformName) const noexcept;
        /**
         * @brief Checks if @b *this is currently @b use by OpenGL.
         * @return true if it is (that means previously binded with this->use(), false otherwise
         */
        bool isCurrentlyUsed(void) const noexcept;
        /**
         * @brief Returns a container filled with the id of every shaders attached to @b *this
         * @return This set of shaders within a vector.
         */
        std::vector<GLuint> getShaders(void) const noexcept;
        /**
         * @brief 
         * 1->4 int;
         * 1->4 uint
         * vecF
         * Matrix
         * count + float/int/uint*
         * matrix 2->4, OxP avec O,P[2, 4] --> count, transpose, float*
         */
        /*template<typename... RegularGLType>
        bool setUniform(const std::string& uniformName, const RegularGLType&... values);*/
    
    protected:
        GLuint                               _id;        //!< The name of this program inside OpenGL.
        mutable std::map<std::string, GLint> _locations; //!< A storage for the uniforms locations.
        
        /**
         * @brief Finds the uniform named @b uniformName location within this program.
         * @details If it was found, store the location into the internal buffer for further usage.
         * @param[in] uniformName The uniforma name you wanna find.
         * @return -1 if it wasn't found, a number greater than 0 otherwise.
         */
        GLint uniformLocation(const std::string& uniformName) const noexcept;
        
    
};


#endif
