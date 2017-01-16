/**
 * @file Shader.hpp
 * @brief Offers an OpenGL wrapper for every action with shaders, like loading, unloading
 * parsing, compiling, etc.
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_SHADER_HPP_INCLUDED
#define MTLKIT_SHADER_HPP_INCLUDED

#include <type_traits> // For std::(true|false)_type
#include <string>      // For std::string
#include <stdexcept>   // For std::runtime_error
#include <iostream>    // For std::ios_base::failure
#include <fstream>     // For std::ifstream
#include <sstream>     // For std::stringbuf

#include "GlCore.hpp"


//! @cond SKIP_THIS_DOXYGEN
namespace _shader_trait // Do not try to use that.
{
	/*
	 * Ladies and gentlemen, this is a trait.
	 * Ugly isn't it ?
	 * It ensures than the GLenum given as a template parameter for the Shader class
	 * is valid.
	 */
    template<GLenum T> struct _is_valid_GLenum                            : public std::false_type {};
    template<>         struct _is_valid_GLenum<GL_FRAGMENT_SHADER>        : public std::true_type  {};
    template<>         struct _is_valid_GLenum<GL_VERTEX_SHADER>          : public std::true_type  {};
    template<>         struct _is_valid_GLenum<GL_COMPUTE_SHADER>         : public std::true_type  {};
	template<>         struct _is_valid_GLenum<GL_TESS_CONTROL_SHADER>    : public std::true_type  {};
	template<>         struct _is_valid_GLenum<GL_TESS_EVALUATION_SHADER> : public std::true_type  {};
	template<>         struct _is_valid_GLenum<GL_GEOMETRY_SHADER>        : public std::true_type  {};
}
//! @endcond


/**
 * @class Shader
 * @brief This is a common wrapper for a shader.
 * 
 * You could also find a way to avoid template parameter by using the typedefs at the end of the file.
 * 
 * \b SHADERTYPE must be :
 *    - \b GL_FRAGMENT_SHADER
 *    - \b GL_VERTEX_SHADER
 *    - \b GL_COMPUTE_SHADER
 *    - \b GL_GEOMETRY_SHADER 
 *    - \b GL_TESS_EVALUATION_SHADER 
 *    - \b GL_TESS_CONTROL_SHADER
 * 
 * Usage :
 * @code
 * // Loading a shader.
 * FragmentShader frag;
 * frag.load("fragment.glsl");
 * // or
 * VertexShader vertex("vertex.glsl");
 * // or by a dirty way
 * char dirt[] = "#version 330\nvoid main(void){}";
 * fragment.loadFromLocal(dirt); // If you're dirty enough to do this.
 * 
 * // possible usages
 * vertex.id();                       // --> GLuint, as const or not.
 * vertex.type();                     // --> GLenum, as const or not.
 * glAttachShader(programId, vertex); // Yes it works !
 * vertex.reload();                   // If you change something on the source file.
 * std::string code = vertex.code();  // as const or not.
 * @endcode
 * Multiple functions throws exceptions if there is issues (std::ios_base::failure && std::runtime_error).
 * Handle them or correct your code.
 */
template<GLenum SHADERTYPE>
class Shader
{
    public:
        /**
         * @brief Create a whole new shader, and load source code from the file <b>shaderSource</b>.
         * @param[in] shaderSource The name of the glsl file you wanna load.
         * @pre <b>shaderSource</b> must be a valid glsl file
         * @pre <b>shaderSource</b> must exist and being accessible in read.
         * @pre <b>shaderSource</b> is not nullptr or NULL.
         * @post Your shader is loaded, compiled, and ready to be link to a program.
         * @throw std::ios_base::failure If there is any trouble by reading <b>shaderSource</b>.
         * @throw std::runtime_error     If there is any error   by compiling the source code.
         * 
         * @code
         * Shader<GL_VERTEX_SHADER> vertex("vertex.glsl");
         * @endcode
         */
        Shader(const GLchar *const shaderSource) : Shader()
        {
            this->load(shaderSource);
            this->_memName = std::string(shaderSource);
        }
        /**
         * @brief Create a whole new shader, and load source code from the file <b>shaderSource</b>.
         * @param[in] shaderSource The name of the glsl file you wanna load.
         * @pre <b>shaderSource</b> must be a valid glsl file
         * @pre <b>shaderSource</b> must exist and being accessible in read.
         * @post Your shader is loaded, compiled, and ready to be link to a program.
         * @throw std::ios_base::failure If there is any trouble by reading <b>shaderSource</b>.
         * @throw std::runtime_error     If there is any error   by compiling the source code.
         * 
         * @code
         * std::string str = findFileName(); 
         * Shader<GL_VERTEX_SHADER> vertex(str);
         * @endcode
         */
        Shader(const std::string& shaderSource) : Shader(shaderSource.c_str())
        {
            
        }
        /**
         * @brief Just create a shader name for OpenGL.
         * @post You shader has a name inside OpenGL context.
         * 
         * @code
         * Shader<GL_FRAGMENT_SHADER> fragment;
         * // or
         * Shader<GL_VERTEX_SHADER> vertex();
         * @endcode
         */
        Shader(void) : _id(0), _memName("")
        {
            const GLuint INVALID_SHADER_NAME = 0;
            this->_id = glCreateShader(SHADERTYPE);
            if (this->_id == INVALID_SHADER_NAME)
            {
                throw std::runtime_error("Failed to create a shader !");
            }
        }
        /**
         * @brief Return the current type of this shader, as a read only shader.
         * @return A valid Shader GLenum.
         * 
         * @code
         * const Shader<GL_VERTEX_SHADER> vertex();
         * vertex.type(); // returns GL_VERTEX_SHADER
         * @endcode
         */
        inline GLenum type(void) const noexcept
        {
            return SHADERTYPE;
        }
        /**
         * @brief Return the current type of this shader, as a read & write shader.
         * @return A valid Shader GLenum.
         * 
         * @code
         * Shader<GL_VERTEX_SHADER> vertex();
         * vertex.type(); // returns GL_VERTEX_SHADER
         * @endcode
         */
        inline GLenum type(void) noexcept
        {
            return SHADERTYPE;
        }
        /**
         * @brief A read only getter for the name of the shader.
         * @return This name, different than 0.
         * 
         * @code
         * const Shader<GL_FRAGMENT_SHADER> fragment("...");
         * fragment.id();
         * @endcode
         */
        inline GLuint id(void) const noexcept
        {
            return this->_id;
        }
        /**
         * @brief A getter for the name of the shader.
         * @return This name, different than 0.
         * 
         * @code
         * Shader<GL_FRAGMENT_SHADER> fragment("...");
         * fragment.id();
         * @endcode
         */
        inline GLuint id(void) noexcept
        {
            return this->_id;
        }
        /**
         * @brief Automaticaly transform your shader into it name for OpenGL, with a read only shader.
         * 
         * @code
         * const Shader<GL_FRAGMENT_SHADER> fragment();
         * // program and co.
         * glAttachShader(program_id, fragment); // For example, as long as the function requires a GLuint.
         * @endcode
         */
        operator GLuint(void) const noexcept
        {
            return this->_id;
        }
        /**
         * @brief Automaticaly transform your shader into it name for OpenGL.
         * 
         * @code
         * Shader<GL_FRAGMENT_SHADER> fragment();
         * // program and co.
         * glAttachShader(program_id, fragment); // For example, as long as the function requires a GLuint.
         * @endcode
         */
        operator GLuint(void) noexcept
        {
            return this->_id;
        }
        /**
         * @brief Gets the source code of the current shader, with a read only shader.
         * @return The source code, as a possible rvalue if existed, an empty string otherwise.
         * 
         * @code
         * const Shader<GL_FRAGMENT_SHADER> fragment("fragment.glsl");
         * std::string code = fragment.code();
         * @endcode
         */
        std::string code(void) const noexcept
        {
            GLint sourceLength;
			glGetShaderiv(this->_id, GL_SHADER_SOURCE_LENGTH, &sourceLength);
			if (sourceLength > 0)
			{
				GLchar* source = new GLchar[sourceLength];
				glGetShaderSource(this->_id, sourceLength, nullptr, source);
				std::string buffer(source);
				delete[] source;
				return buffer;
			}
			return std::string("");
        }
        /**
         * @brief Gets the source code of the current shader.
         * @return The source code, as a possible rvalue if existed, an empty string otherwise.
         * 
         * @code
         * Shader<GL_FRAGMENT_SHADER> fragment("fragment.glsl");
         * std::string code = fragment.code();
         * @endcode
         */
        std::string code(void) noexcept
        {
            const Shader<SHADERTYPE>& ref = const_cast<const Shader<SHADERTYPE>&>(*this);
            return ref.code();
        }
        /**
         * @brief Delete the actual shader !
         */
        virtual ~Shader(void) noexcept
        {
            glDeleteShader(this->_id);
        }
        /**
         * @brief Load and compile shader source code from \b fname.
         * @param[in] fname The valid file name which contains the source code.
         * @throw std::runtime_error     If any problem occurs while parsing.
         * @throw std::ios_base::failure If any trouble happens while opening/reading the file.
         * @pre <b>fname</b> must be a valid glsl file
         * @pre <b>fname</b> must exist and being accessible in read.
         * @pre <b>fname</b> is not nullptr or NULL.
         * @post Your shader has a loaded and compiled source code.
         * 
         * @code
         * Shader<GL_COMPUTE_SHADER> compute;
         * compute.load("compute.glsl");
         * @endcode
         */
        void load(const GLchar *const fname)
        {
            this->compile(this->readShader(fname));
            this->checkSourceErrors(fname);
            if (this->_memName == "")
            {
                this->_memName = std::string(fname);
            }
            this->_src = nullptr;
        }
        /**
         * @brief If you're dirty enough to do that, you can load a shader from a local char* or std::string.
         * You'll have to assume than this char* remains during the whole lifespend of the shader, because
         * he'll try to refers to it when calling code() statements.
         * By the way, it won't delete[] it anymore, you'll have to deal with memory by yourself.
         * @param[in] source The entire source code embedded into a native char*.
         * @pre <b>source</b> is not nullptr or NULL.
         * @post This source code is loaded into your shader, and compiled.
         * @throw std::runtime_error If any problem occurs while parsing.
         * 
         * @code
         * Shader<GL_FRAGMENT_SHADER> fragment;
         * char source[] = "#version 330 ....";
         * fragment.loadFromLocal(source);
         * @endcode
         */
        void loadFromLocal(const GLchar *const source)
        {
            if (source == nullptr)
            {
                throw std::runtime_error("You cannot load shader source from a null pointer");
            }
            this->compile(std::string(source));
            this->checkSourceErrors("raw pointer");
            this->_memName = "";
            this->_src = source;
        }
        /**
         * @brief Reload this shader from the original file.
         * @pre The current shader must have a previously loaded source code file.
         * @post Your source code is reloaded from the same file.
         * @throw std::ios_base::failure If there is issues while loading the file.
         * @throw std::runtime_error     If there is no previously loaded things or errors on the source code.
         * 
         * @code
         * Shader<GL_FRAGMENT_SHADER> fragment("fragment.glsl");
         * // modify fragment.glsl during execution
         * fragment.reload();
         * @endcode
         */
        void reload(void)
        {
            if (this->_memName != "")
            {
                this->load(this->_memName.c_str());
            }
            throw std::ios_base::failure("No file loaded in this shader for reloading");
        }
        
    protected:
        GLuint        _id;      //!< The name of the shader inside OpenGL.
        std::string   _memName; //!< Memorize the source file name, to reload it if needed.
        const GLchar* _src;     //!< A dirty storage for a dirty way to create shader.
        
    private:
        static_assert(_shader_trait::_is_valid_GLenum<SHADERTYPE>::value, "Invalid shader type !");
        
        Shader(const Shader& other)            = delete;
        Shader(Shader&& other)                 = delete;
        Shader& operator=(const Shader& other) = delete;
        Shader& operator=(Shader&& other)      = delete;
        
        /**
         * @brief Read and store the shader source extracted from \b fname into a std::string.
         * @param[in] fname The name of the file.
         * @return The container of the source code, as a rvalue.
         * @pre <b>fname</b> must exist and being accessible in read.
         * @throw std::ios_base::failure If there is issue with the file.
         */
        std::string readShader(const GLchar *const fname) const
        {
            // Credits to Jean-Claude Iehl from Universite Lyon 1 for this code.
            std::ifstream source(fname);
            if (!source.good())
            {
                throw std::ios_base::failure(std::string("[Shader] : Unable to load ") + fname);
            }
            std::stringbuf content;
            source.get(content, '\0');
            return content.str();
        }
        /**
         * @brief Compile the shader source code <b>source</b>.
         * @param[in] source A std::string which contains the all source code.
         */
        void compile(const std::string& source) noexcept
        {
            const GLint NB_SHADER_SOURCE = 1;
            const GLchar* entry[NB_SHADER_SOURCE] = {source.c_str()};
            glShaderSource(this->_id, NB_SHADER_SOURCE, entry, nullptr);
            glCompileShader(this->_id);
        }
        /**
         * @brief Ensure than there is no errors with the source code.
         * @param[in] sourceName The parsed source file name.
         * @throw std::runtime_error If there is any mistake with the source code. 
         */
        void checkSourceErrors(const GLchar *const sourceName) const
        {
            GLint status;
            glGetShaderiv(this->_id, GL_COMPILE_STATUS, &status);
            if (status != GL_TRUE)
            {
                GLint length;
                glGetShaderiv(this->_id, GL_INFO_LOG_LENGTH, &length);
                GLchar* message = new char[length];
                GLsizei maxLength;
                glGetShaderInfoLog(this->_id, length, &maxLength, message);
                std::stringstream fullMessage;
                fullMessage << "Error with " << sourceName << std::endl
                            << message       << std::endl;
                delete[] message;
                throw std::runtime_error(fullMessage.str());
            }
        }
    
};

typedef Shader<GL_FRAGMENT_SHADER>        FragmentShader;       //!< A simple way to instanciate a fragment        shader.
typedef Shader<GL_VERTEX_SHADER>          VertexShader;         //!< A simple way to instanciate a vertex          shader.
typedef Shader<GL_COMPUTE_SHADER>         ComputeShader;        //!< A simple way to instanciate a compute         shader.
typedef Shader<GL_GEOMETRY_SHADER>        GeometryShader;       //!< A simple way to instanciate a geometry        shader.
typedef Shader<GL_TESS_EVALUATION_SHADER> TessEvaluationShader; //!< A simple way to instanciate a tess_evaluation shader.
typedef Shader<GL_TESS_CONTROL_SHADER>    TessControlShader;    //!< A simple way to instanciate a tess_control    shader.

#endif
