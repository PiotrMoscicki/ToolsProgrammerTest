#pragma once

#include <vector>

#include "Structures/Point.hpp"

namespace TPT
{
	struct Scene
	{
		size_t ResolutionX = 256;
		size_t ResolutionY = 256;

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