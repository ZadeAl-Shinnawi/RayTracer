/*
 * This class provides the concept of a mathematical vector and is utilized
 * extensively throughout the entirety of the codebase for various uses.
 */

#pragma once

#include <cmath>
#include <ostream>
#include <array>

#include "utilities.h"

struct Vector3
{
public:
	// Default constructor.
	Vector3() : vals{0.0f, 0.0f, 0.0f} {}

	// Initialization constructor.
	Vector3(float vals0, float vals1, float vals2) : vals{vals0, vals1, vals2}
	{}

	float x() const
	{
		return vals[0];
	}

	float y() const
	{
		return vals[1];
	}

	float z() const
	{
		return vals[2];
	}

	float magnitude() const
	{
		return sqrt(magnitudeSquared());
	}

	float magnitudeSquared() const
	{
		return vals[0] * vals[0] + vals[1] * vals[1] + vals[2] * vals[2];
	}

	float operator[](int i) const
	{
		return vals[i];
	}

	float& operator[](int i)
	{
		return vals[i];
	}

	Vector3 operator-() const
	{
		return Vector3(-vals[0], -vals[1], -vals[2]);
	}

	Vector3& operator+=(const Vector3& v)
	{
		vals[0] += v.vals[0];
		vals[1] += v.vals[1];
		vals[2] += v.vals[2];

		return *this;
	}

	Vector3& operator*=(const float t)
	{
		vals[0] *= t;
		vals[1] *= t;
		vals[2] *= t;

		return *this;
	}

	Vector3& operator/=(const float t)
	{
		return *this *= 1.0f / t;
	}

	// Returns a vector with random components in the range [0, 1).
	inline static Vector3 random()
	{
		return Vector3(randomFloat(), randomFloat(), randomFloat());
	}

	// Returns a vector with random components in the range [min, max).
	inline static Vector3 random(float min, float max)
	{
		return Vector3(randomFloat(min, max),
					randomFloat(min, max),
					randomFloat(min, max));
	}

	bool nearZero() const
	{
		// Return true if the vector is close to zero in all dimensions.
		const float s = 1e-8f;

		return (fabs(vals[0]) < s) &&
			   (fabs(vals[1]) < s) &&
			   (fabs(vals[2]) < s);
	}

	// Represents the standard basis vector.
	std::array<float, 3> vals;
};

// Position vector type alias.
using Point3 = Vector3;

// Color vector type alias.
using Color = Vector3;

// Prints to standard output.
inline std::ostream& operator<<(std::ostream& out, const Vector3& u)
{
	return out << u.vals[0] << ' ' << u.vals[1] << ' ' << u.vals[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v)
{
	return Vector3(u.vals[0] + v.vals[0],
				   u.vals[1] + v.vals[1],
				   u.vals[2] + v.vals[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v)
{
	return Vector3(u.vals[0] - v.vals[0],
				   u.vals[1] - v.vals[1],
				   u.vals[2] - v.vals[2]);
}

// Multiplies two vectors.
inline Vector3 operator*(const Vector3& u, const Vector3& v)
{
	return Vector3(u.vals[0] * v.vals[0],
				   u.vals[1] * v.vals[1],
				   u.vals[2] * v.vals[2]);
}

// Multiplies a float and a vector.
inline Vector3 operator*(float t, const Vector3& u)
{
	return Vector3(t * u.vals[0], t * u.vals[1], t * u.vals[2]);
}

// Multiplies a vector and a float.
inline Vector3 operator*(const Vector3& u, float t)
{
	return t * u;
}

inline Vector3 operator/(Vector3 u, float t)
{
	return (1 / t) * u;
}

// Vector dot product: u = <a, b, c>, v = <d, e, f>
// u dot v = a * d + b * e + c * f
inline float dot(const Vector3& u, const Vector3& v)
{
	return u.vals[0] * v.vals[0] +
		   u.vals[1] * v.vals[1] +
		   u.vals[2] * v.vals[2];
}

// Vector cross product: u = <a, b, c>, v = <d, e, f>
// u cross v = <bf - ce, cd - af, ae - bd>
inline Vector3 cross(const Vector3& u, const Vector3& v)
{
	return Vector3(u.vals[1] * v.vals[2] - u.vals[2] * v.vals[1],
				   u.vals[2] * v.vals[0] - u.vals[0] * v.vals[2],
				   u.vals[0] * v.vals[1] - u.vals[1] * v.vals[0]);
}

inline Vector3 unitVector(Vector3 u)
{
	return u / u.magnitude();
}

// Returns a random vector within the unit sphere.
inline Vector3 randUnitSphereVector()
{
	while (true)
	{
		Vector3 p = Vector3::random(-1, 1);
		if (p.magnitudeSquared() >= 1) continue;

		return p;
	}
}

// Returns a random unit vector within the unit sphere.
inline Vector3 randUnitVector()
{
	return unitVector(randUnitSphereVector());
}

// Returns a random vector within the hemisphere.
inline Vector3 randHemisphereVector(const Vector3& normal)
{
	Vector3 inUnitSphere = randUnitSphereVector();

	// In the same hemisphere as the normal
	if (dot(inUnitSphere, normal) > 0.0)
		return inUnitSphere;
	else
		return -inUnitSphere;
}

// Returns a random vector within the unit disk.
inline Vector3 randomInUnitDisk()
{
	while (true)
	{
		Vector3 p = Vector3(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), 0.0f);

		if (p.magnitudeSquared() >= 1) continue;

		return p;
	}
}

// Returns a reflection direction vector.
inline Vector3 reflect(const Vector3& v, const Vector3& n)
{
	return v - 2 * dot(v, n) * n;
}

// Returns a refraction direction vector.
inline Vector3 refract(const Vector3& uv, const Vector3& n, float etaiOverEtat)
{
	float cosTheta = fmin(dot(-uv, n), 1.0f);

	Vector3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);
	Vector3 rOutParallel = -sqrt(fabs(1.0f - rOutPerp.magnitudeSquared())) * n;

	return rOutPerp + rOutParallel;
}
