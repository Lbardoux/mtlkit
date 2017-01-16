/**
 * @file Pipeline_traits.hpp
 * @brief Offers multiples traits to ensure that you're using the Pipeline class properly.
 * Because this is better to get trouble when compiling than during runtime.
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_PIPELINE_TRAITS_HPP_INCLUDED
#define MTLKIT_PIPELINE_TRAITS_HPP_INCLUDED

#include "GlCore.hpp"
#include <type_traits>
#include <cstdint>

/**
 * @brief Checks if \b f is a valid depth function enum.
 * @param[in] f The GLenum you want as a depth function.
 * @return true if everything is OK, false otherwise.
 */
bool is_valid_depth_function_enum(GLenum f) noexcept;

#endif

