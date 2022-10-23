#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <ostream>

template<class T>
class vec2
{
	public:
		
		T x;
		T y;

		vec2()
			: x{0.0}, y {0.0} {};

		vec2(T x, T y)
			: x {x}, y {y} {};

		friend std::ostream& operator << (std::ostream& stream, const vec2& vec)
		{
			return stream << vec.x << ' ' << vec.y;
		}

		vec2 operator + (const vec2& right_vector)
		{
			return vec2(x + right_vector.x, y + right_vector.y);
		}
		vec2 operator - (const vec2& right_vector)
		{
			return vec2(x - right_vector.x, y - right_vector.y);
		}
		vec2 operator * (const vec2& right_vector)
		{
			return vec2(x * right_vector.x, y * right_vector.y);
		}
		vec2 operator / (const vec2& right_vector)
		{
			return vec2(x / right_vector.x, y / right_vector.y);
		}
		vec2 operator % (const vec2& right_vector)
		{
			return vec2(x % right_vector.x, y % right_vector.y);
		}
};

using vec2i = vec2<int32_t>;
using vec2u = vec2<uint32_t>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;

#endif
