#pragma once

#include "Structures/ICommand.hpp"
#include "Structures/Point.hpp"

namespace TPT
{
	class IPointModificationCommand : public ICommand
	{
	public:
		virtual void SetPoint(Point* point) = 0;
	};
}