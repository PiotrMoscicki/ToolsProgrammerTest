#pragma once

#include <QtGui/qvector3d.h>

namespace TPT
{
	class Point
	{
	public:
		Point() : Id(IdGenerator) { ++IdGenerator; }
		Point(size_t id) : Id(id) {}

		QVector3D Position = QVector3D{ 0, 0, 0 };

		const size_t Id;

	private:
		static size_t IdGenerator;
	};
}