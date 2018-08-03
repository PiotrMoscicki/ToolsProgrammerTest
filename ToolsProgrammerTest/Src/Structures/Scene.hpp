#pragma once

#include <vector> 
#include <QtGui/qimage.h>
#include <QtGui/qvector3d.h>

namespace TPT
{
	struct Scene
	{
		std::vector<QVector3D*> Points;
		QImage* HeightMap;
	};
}