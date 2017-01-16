/**
 * @file Pipeline.hpp
 * @brief Offers a way to modify/access OpenGL's render pipeline parameters.
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_PIPELINE_HPP_INCLUDED
#define MTLKIT_PIPELINE_HPP_INCLUDED

#include "GlCore.hpp"
#include "Pipeline_traits.hpp"
#include "vec.hpp"
#include <string>


/**
 * @class Pipeline
 * @brief This is the handy way to access pipeline' parameters values.
 */
class Pipeline final
{
	public:
		/**
		 * @brief Return the current binded depth function to the pipeline.
		 * @return GL_LESS | GL_EQUAL | GL_LEQUAL | GL_NEVER | GL_GREATER | GL_NOTEQUAL
		 * | GL_GEQUAL | GL_ALWAYS, with GL_LESS as a default value.
		 */
		static GLenum depthTestFunction(void) noexcept;
		/**
		 * @brief Sets \b function as the new current depth function.
		 * @param[in] function A valid GLenum value for the depth test function.
		 * @pre \b function must match valid values (see below).
		 * @throw std::invalid_argument If you provides a wrong GLenum.
		 */
		static void depthTestFunction(GLenum function);
		/**
		 * @brief Checks if the depth test is enable or not.
		 * @return GL_TRUE if depthTest is enable, GL_FALSE otherwise.
		 */
		static GLboolean depthTest(void) noexcept;
		/**
		 * @brief Enable/disable the depth test.
		 * @param[in] enable true if you want the depth test, false otherwise.
		 */
		static void depthTest(bool enable) noexcept;
		/**
		 * @brief Grants access to the actual clear depth value as a float.
		 * @return This value as a float.
		 */
		static GLfloat depthClearValue(void) noexcept;
		/**
		 * @brief Sets the depth clear value with \b value.
		 * @param[in] value The clear depth value you wanna put.
		 */
		static void depthClearValue(GLfloat value) noexcept;
		/**
		 * @brief Grants access to the actually binded clear color of the pipeline.
		 * @return These values inside a Color structure.
		 */
		static Color clearColor(void) noexcept;
		/**
		 * @brief Sets the clear color with a Color structure \b color.
		 * @param[in] color The color you wanna set.
		 */
		static void clearColor(const Color& color) noexcept;
		/**
		 * @brief Sets the clear color with <b>r, g, b, a</b>.
		 * @param[in] r The red   value, between 0.0f and 1.0f.
		 * @param[in] g The green value, between 0.0f and 1.0f.
		 * @param[in] b The blue  value, between 0.0f and 1.0f.
		 * @param[in] a The alpha value, between 0.0f and 1.0f.
		 */
		static void clearColor(GLfloat r=0.0f, GLfloat g=0.0f, GLfloat b=0.0f, GLfloat a=1.0f) noexcept;
		/**
		 * @brief Checks if the cullfacing is enabled.
		 * @return GL_TRUE if this is enabled, GL_FALSE otherwise.
		 */
		static GLboolean culling(void) noexcept;
		/**
		 * @brief Enable/disable face culling.
		 * @param[in] enable GL_TRUE | GL_FALSE.
		 */
		static void culling(GLboolean enable) noexcept;
		/**
		 * @brief Sets the way OpenGL elects the faces to display by their
		 * rotation sense.
		 * @param[in] direction GL_CW (clockwise), or GL_CCW (counter clockwise).
		 * @throw std::runtime_error If you provides a wrong enum for \b direction.
		 */
		static void rotationDirection(GLenum direction);
		/**
		 * @brief Gets the OpenGL rotation direction.
		 * @return GL_CW or GL_CCW.
		 */
		static GLenum rotationDirection(void) noexcept;
		/**
		 * @brief Sets the cullface face to keep to \b type.
		 * @param[in] type GL_FRONT, GL_BACK, GL_FRONT_AND_BACK.
		 */
		static void cullFace(GLenum type);
		/**
		 * @brief Gets the current cullface enum.
		 * @return GL_BACK, GL_FRONT, GL_FRONT_AND_BACK.
		 */
		static GLenum cullFace(void) noexcept;
		/**
		 * @brief Clear buffers which you specify true.
		 * @param[in] depth   The depth       buffer you wanna clear with the default value.
		 * @param[in] color   The color       buffer you wanna clear with the default value.
		 * @param[in] accum   The accumulator buffer you wanna clear with the default value.
		 * @param[in] stencil The stencil     buffer you wanna clear with the default value.
		 */
		static void clear(bool depth=false, bool color=false, bool accum=false, bool stencil=false) noexcept;
		
		/**
		 * @brief Load the pipeline configuration from \b fname
		 * @param[in] fname A well formated xml file.
		 * @throw std::ios_base::failure If there is issue with the file.
		 * @throw std::runtime_error     If the file is ill-formated.
		 */
		static void fromXML(const GLchar* fname);
		
	private:
		Pipeline(void) = delete;
};

#endif

