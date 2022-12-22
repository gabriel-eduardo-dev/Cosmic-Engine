#ifndef COLOR_HPP
#define COLOR_HPP

#include "Types.hpp"

class Color 
{
	public:

		f32 r, g, b, a;

		Color()
			: r {0}, g {0}, b {0}, a {255.0} {converter();}
		Color(float r, float g, float b, float a)
			: r {r}, g {g}, b {b}, a {a} {converter();}
		Color(float r, float g, float b)
			: r {r}, g {g}, b {b}, a {255.0} {converter();}

		void converter()
		{
			r /= 255;
			g /= 255;
			b /= 255;
			a /= 255;
		}
};

#endif
