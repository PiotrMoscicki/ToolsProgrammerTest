#pragma once

#include <vector>

#include "Structures/Point.hpp"

namespace TPT
{
	struct Scene
	{
		size_t ResolutionX = 255;
		size_t ResolutionY = 100;
		size_t ResolutionZ = 255;

		Point* GetPointById(size_t id)
		{
			for (auto point : Points)
				if (point->Id == id)
					return point;

			throw new std::exception;
		}

		std::vector<Point*> Points;
	};
}