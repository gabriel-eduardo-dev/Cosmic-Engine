#include "Polygons.hpp"

namespace Polygons
{
	namespace Square
	{
		F32 vertices[4 * 3] = 
		{
			1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
		};
		UINT32 indices[2 * 3] =
		{
			0, 1, 3, 
		    1, 2, 3,
		};
		F32 text_cords[4 * 3] =
		{
			1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
		};
	}
	namespace Cube
	{
		F32 vertices[8 * 3] =
		{
			-1.0f,  1.0f, 0.0, 
			 1.0f,  1.0f, 0.0,
			-1.0f, -1.0f, 0.0,
			 1.0f, -1.0f, 0.0,

			-1.0f,  1.0f, -1.0, 
			 1.0f,  1.0f, -1.0,
			-1.0f, -1.0f, -1.0,
			 1.0f, -1.0f, -1.0,
		};

		UINT32 indices[12 * 3] =
		{
			0, 1, 2,
			2, 1, 3,

			4, 5, 6,
			6, 7, 5,

			0, 2, 6,
			0, 4, 6,

			3, 7, 1,
			1, 5, 7,

			0, 1, 4,
			1, 4, 5,

			3, 6, 7,
			3, 2, 6,
		};
	}
	namespace Triangle
	{
		F32 vertices[3 * 3] =
		{
			0.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
		};
	}
}
