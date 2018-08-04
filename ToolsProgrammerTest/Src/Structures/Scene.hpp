#pragma once

#include <vector> 
#include <QtGui/qvector3d.h>

namespace TPT
{
	struct Scene
	{
		std::vector<QVector3D*> Points;
	};
}