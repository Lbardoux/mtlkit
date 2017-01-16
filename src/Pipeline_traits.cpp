#include <vector>
#include <initializer_list>
#include <algorithm>

#include "GlCore.hpp"
#include "Pipeline_traits.hpp"


namespace // GLenum legal values.
{
	const std::vector<GLenum> depthFunc({
		GL_LESS, GL_NEVER, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS
	});
	
	bool find(const std::vector<GLenum>& legals, GLenum value)
	{
		return std::find(legals.begin(), legals.end(), value) != legals.end();
	}
}


bool is_valid_depth_function_enum(GLenum f) noexcept
{
	return find(depthFunc, f);
}
