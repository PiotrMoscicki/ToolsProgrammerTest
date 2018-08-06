#pragma once

#include "Structures/Point.hpp"

namespace TPT
{
	struct Scene
	{
		std::map<size_t, Point*> Points;
	};
}