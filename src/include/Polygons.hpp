#ifndef POLYGONS_HPP
#define POLYGONS_HPP

#include "Types.hpp"

namespace Polygons 
{
	namespace Square
	{
		extern F32 vertices[4 * 3];
		extern UINT32 indices[2 * 3];
		extern F32 text_cords[4 * 3];
	}
	namespace Cube
	{
		extern F32 vertices[8 * 3];
		extern UINT32 indices[12 * 3];
	}
	namespace Triangle
	{
		extern F32 vertices[3 * 3];
	}
}

#endif
