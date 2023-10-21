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
					auto center2 = center + Vector3(0, randomFloat(0, .5), 0);
					world.add(std::make_shared<Sphere>(center, center2, 0.2, sphereMaterial));
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
	const float ASPECT_RATIO = 16.0f / 9.0f;
	const int IMAGE_WIDTH = 1200;
	const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
	const int SAMPLES_PER_PIXEL = 500;
	const int MAX_DEPTH = 50;
	bool msaa = true;

	// Create hittable list and add primitives to world.
	HittableList world = randomScene();

	Camera camera(IMAGE_WIDTH, IMAGE_HEIGHT, SAMPLES_PER_PIXEL, MAX_DEPTH, ASPECT_RATIO, 20.0f, .02f, 10.0f,
				  Point3(13.0f, 2.0f, 3.0f), Point3(0.0f, 0.0f, 0.0f),
				  Vector3(0.0f, 1.0f, 0.0f));

	camera.render(world);

	return 0;
}
