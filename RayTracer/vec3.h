/*
 *	This class contains information on the Vec3 object which is utilized
 *  extensively to represent a myriad of different, crucial components in
 *	the ray tracer such as rays, colors, and points.
 */

#pragma once

#include <cmath>
#include <ostream>
#include <array>

class Vec3
{
public:
	// Default Constructor: Initializes vector components to 0.
	Vec3() : e{0.0f, 0.0f, 0.0f} {}

	// Constructor: Initializes vector components to specified values.
	Vec3(float elt0, float elt1, float elt2) : e{elt0, elt1, elt2} {}

	// REQUIRES: Nothing.
	// MODIFIES: Nothing.
	// EFFECTS:  Returns the x-component of the vector.
	float getX() const
	{
		return e[0];
	}

	// REQUIRES: Nothing.
	// MODIFIES: Nothing.
	// EFFECTS:  Returns the y-component of the vector.
	float getY() const
	{
		return e[1];
	}

	// REQUIRES: Nothing.
	// MODIFIES: Nothing.
	// EFFECTS:  Returns the z-component of the vector.
	float getZ() const
	{
		return e[2];
	}

	// REQUIRES: Nothing.
	// MODIFIES: Nothing.
	// EFFECTS:  Returns the magnitude of the given vector.
	float length() const
	{
		return sqrt(lengthSquared());
	}

	// REQUIRES: Nothing.
	// MODIFIES: Nothing.
	// EFFECTS:  Returns the squared magnitude of the given vector.
	float lengthSquared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	// REQUIRES: Integer i must be in the range [0, 2].
	// MODIFIES: Nothing.
	// EFFECTS:  Returns the i'th component of the vector.
	float operator[](int i) const
	{
		return e[i];
	}

	// REQUIRES: Integer i must be in the range [0, 2].
	// MODIFIES: The i'th vector component.
	// EFFECTS:  Returns a reference to the i'th component of the vector.
	float& operator[](int i)
	{
		return e[i];
	}

	// REQUIRES: Nothing.
	// MODIFIES: Nothing.
	// EFFECTS:  Returns a vector with negated components.
	Vec3 operator-() const
	{
		return Vec3(-e[0], -e[1], -e[2]);
	}

	// REQUIRES: Nothing.
	// MODIFIES: The vector components.
	// EFFECTS:  Sums the components of each vector.
	Vec3& operator+=(const Vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];

		return *this;
	}

	// REQUIRES: Nothing.
	// MODIFIES: The vector components.
	// EFFECTS:  Multiplies each component of the vector by t.
	Vec3& operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;

		return *this;
	}

	// REQUIRES: Nothing.
	// MODIFIES: The vector components.
	// EFFECTS:  Divides each component of the vector by t.
	Vec3& operator/=(const float t)
	{
		return *this *= 1.0f / t;
	}

	// Represents the standard basis vector.
	std::array<float, 3> e;
};

// Position vector type alias.
using Point3 = Vec3;

// Color vector type alias.
using Color = Vec3;

// REQUIRES: Nothing.
// MODIFIES: Standard output (cout).
// EFFECTS:  Outputs vector components.
inline std::ostream& operator<<(std::ostream& out, const Vec3& u)
{
	return out << u.e[0] << ' ' << u.e[1] << ' ' << u.e[2];
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns a vector whose components sum to those in u and v.
inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns a vector whose components are
//			 the difference of those in u and v.
inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns a vector whose components are
//			 the product of those in u and v.
inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns a vector whose components are the
//			 product of the value t and those in u.
inline Vec3 operator*(float t, const Vec3& u)
{
	return Vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns a vector whose components are the
//			 product of those in u and the value t.
inline Vec3 operator*(const Vec3& u, float t)
{
	return t * u;
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns a vector whose quotients are
//			 the components of u divided by t.
inline Vec3 operator/(Vec3 u, float t)
{
	return (1 / t) * u;
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns the dot product of u and v.
inline float dot(const Vec3& u, const Vec3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns the cross product of u and v.
// u = <a, b, c>, v = <d, e, f>
// u cross v = <bf - ce, cd - af, ae - bd>
inline Vec3 cross(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// REQUIRES: Nothing.
// MODIFIES: Vector u.
// EFFECTS:  Returns the unit vector of u.
inline Vec3 unitVector(Vec3 u)
{
	return u / u.length();
}