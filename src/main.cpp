#include <iostream>
#include <memory>
#include <cmath>
#include "Math/vector3.h"
#include "Math/ray.h"
#include "Math/color.h"
#include "Math/utilities.h"
#include "Geometry/sphere.h"
#include "Hittables/hittableList.h"
#include "Camera/camera.h"
#include "Materials/material.h"
#include "Materials/diffuse.h"
#include "Materials/metal.h"
#include "Materials/glass.h"

HittableList randomScene()
{
	HittableList world;

	auto groundMaterial = std::make_shared<Diffuse>(Color(0.5f, 0.5f, 0.5f));
	world.add(std::make_shared<Sphere>(Point3(0.0f, -1000.0f, 0.0f), 1000.0f,
									   groundMaterial));

	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			float chooseMat = randomFloat();
			Point3 center(a + (0.9f * randomFloat()), 0.2f,
						  b + (0.9f * randomFloat()));

			if ((center - Point3(4.0f, 0.2f, 0.0f)).magnitude() > 0.9f)
			{
				std::shared_ptr<Material> sphereMaterial;

				if (chooseMat < 0.8f)
				{
					// Diffuse
					Vector3 albedo = Color::random() * Color::random();
					sphereMaterial = std::make_shared<Diffuse>(albedo);
					world.add(std::make_shared<Sphere>
							 (center, 0.2f, sphereMaterial));
				}
				else if (chooseMat < 0.95f)
				{
					// Metal
					Vector3 albedo = Color::random(0.5f, 1.0f);
					float fuzz = randomFloat(0.0f, 0.5f);
					sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>
							 (center, 0.2f, sphereMaterial));
				}
				else
				{
					// Glass
					sphereMaterial = std::make_shared<Glass>(1.5f);
					world.add(std::make_shared<Sphere>
							 (center, 0.2f, sphereMaterial));
				}
			}
		}
	}

	auto material1 = std::make_shared<Glass>(1.5f);
	world.add(std::make_shared<Sphere>
			 (Point3(0.0f, 1.0f, 0.0f), 1.0f, material1));

	auto material2 = std::make_shared<Diffuse>(Color(0.4f, 0.2f, 0.1f));
	world.add(std::make_shared<Sphere>
			 (Point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

	auto material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
	world.add(std::make_shared<Sphere>
			 (Point3(4.0f, 1.0f, 0.0f), 1.0f, material3));

	return world;
}

int main()
{
	// Image
	const float ASPECT_RATIO = 3.0f / 2.0f;
	const int IMAGE_WIDTH = 1200;
	const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
	const int SAMPLES_PER_PIXEL = 500;
	const int MAX_DEPTH = 50;
	bool msaa = true;

	// Used for MSAA.
	Vector3 horizontal = Vector3(3.556f, 0.0f, 0.0f);
	Vector3 vertical = Vector3(0.0f, 2.0f, 0.0f);
	Vector3 lowerLeftCorner = Point3(0.0f, 0.0f, 0.0f) - (horizontal / 2.0f) - 
						   (vertical / 2.0f) - Vector3(0.0f, 0.0f, 1.0f);

	// Create hittable list and add primitives to world.
	HittableList world = randomScene();

	// Create camera.
	Point3 lookFrom(13.0f, 2.0f, 3.0f);
	Point3 lookAt(0.0f, 0.0f, 0.0f);
	Vector3 vUp(0.0f, 1.0f, 0.0f);

	float distToFocus = 10.0f;
	float aperture = 0.1f;

	Camera cam(lookFrom, lookAt, vUp, ASPECT_RATIO,
			   90.0f, aperture, distToFocus);

	// Output necessary information to PPM file.
	std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

	// Iterate through all pixels.
	for (int j = IMAGE_HEIGHT - 1; j >= 0; --j)
	{
		// Output pixel progress
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < IMAGE_WIDTH; ++i)
		{
			// Check if MSAA is enabled.
			if (!msaa)
			{
				float u = static_cast<float>(i) / (IMAGE_WIDTH - 1);
				float v = static_cast<float>(j) / (IMAGE_HEIGHT - 1);
				Ray r(Point3(0.0f, 0.0f, 0.0f), lowerLeftCorner +
					 (u * horizontal) +
					 (v * vertical));
				Color pixelColor = rayColor(r, world, MAX_DEPTH);
				writeColor(std::cout, pixelColor, 0, false);
				continue;
			}

			Color pixelColor;
			for (int samples = 0; samples < SAMPLES_PER_PIXEL; ++samples)
			{
				// Sample random points within pixel.
				float u = (i + randomFloat()) / (IMAGE_WIDTH - 1);
				float v = (j + randomFloat()) / (IMAGE_HEIGHT - 1);
				Ray r = cam.getRay(u, v);
				pixelColor += rayColor(r, world, MAX_DEPTH);
			}

			// Record current pixel color in PPM file.
			writeColor(std::cout, pixelColor, SAMPLES_PER_PIXEL, true);
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}