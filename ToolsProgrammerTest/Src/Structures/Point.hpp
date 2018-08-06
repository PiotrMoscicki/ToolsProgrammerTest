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

		QString Name = "";
		QVector3D Position = QVector3D{ 0, 0, 0 };

		const size_t Id;
	};
}