#pragma once

#include <QtGui/qvector3d.h>
#include <QtCore/qstring.h>

namespace TPT
{
	class Point
	{
	public:
		Point();
		Point(size_t id);
		~Point();

		Point operator=(const Point& p)
		{
			Name = p.Name;
			PosX = p.PosX;
			PosY = p.PosY;
			PosZ = p.PosZ;

			return *this;
		}

		QString Name = "";
		size_t PosX = 0;
		size_t PosY = 0;
		size_t PosZ = 0;

		const size_t Id;
	};
}