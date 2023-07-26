/*
 *	Contains the driver function that combines all types and functions
 *	in the codebase to display the final, desired graphical output.
 */

#include <iostream>
#include <memory>
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "utilities.h"
#include "sphere.h"
#include "hittableList.h"
#include "camera.h"

int main()
{
	// Image
	const float aspectRatio = 16.0f / 9.0f;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio); // 225
	const int samplesPerPixel = 100;
	bool msaa = true;

	// Used for MSAA.
	Vec3 horizontal = Vec3(3.556f, 0.0f, 0.0f);
	Vec3 vertical = Vec3(0.0f, 2.0f, 0.0f);
	Vec3 lowerLeftCorner = Point3(0.0f, 0.0f, 0.0f) - (horizontal / 2.0f) - 
						   (vertical / 2.0f) - Vec3(0.0f, 0.0f, 1.0f);

	// Create hittable list and add primitives to world.
	HittableList world;
	world.add(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.68f));
	world.add(std::make_shared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f));

	// Create camera.
	Camera cam;

	// Output necessary information to PPM file.
	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	// Iterate through all pixels.
	for (int j = imageHeight - 1; j >= 0; --j)
	{
		// Output pixel progress
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < imageWidth; ++i)
		{
			// Check if MSAA is enabled.
			if (!msaa)
			{
				float u = static_cast<float>(i) / (imageWidth - 1);
				float v = static_cast<float>(j) / (imageHeight - 1);
				Ray r(Point3(0,0,0), lowerLeftCorner + (u * horizontal) +
					 (v * vertical));
				Color pixel_color = rayColor(r, world);
				writeColor(std::cout, pixel_color, 0, false);
				continue;
			}

			Color pixelColor;
			for (int samples = 0; samples < samplesPerPixel; ++samples)
			{
				// Sample random points within pixel.
				float u = (i + randomFloat()) / (imageWidth - 1.0f);
				float v = (j + randomFloat()) / (imageHeight - 1.0f);
				Ray r = cam.getRay(u, v);
				pixelColor += rayColor(r, world);
			}

			// Record current pixel color in PPM file.
			writeColor(std::cout, pixelColor, samplesPerPixel, true);
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}