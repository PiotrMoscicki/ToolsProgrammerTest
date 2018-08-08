#pragma once

#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>

#include "Structures/Point.hpp"

namespace TPT
{
	class ISceneManager
	{
	public:
		virtual void SetHeightMap(std::unique_ptr<QPixmap> heightMap) = 0;
		virtual QPixmap* GetHeightMap() = 0;

		virtual Point* SpawnPoint() = 0;
		virtual Point* SpawnPoint(size_t id) = 0;
		virtual void DestroyPoint(size_t id) = 0;
		virtual Point* GetPoint(size_t id) = 0;
		virtual std::vector<Point*> GetPoints() = 0;

		virtual size_t SetSceneResolutionX(size_t value) = 0;
		virtual size_t SetSceneResolutionY(size_t value) = 0;
		virtual size_t SetSceneResolutionZ(size_t value) = 0;

		virtual size_t GetSceneResolutionX() = 0;
		virtual size_t GetSceneResolutionY() = 0;
		virtual size_t GetSceneResolutionZ() = 0;
	};
}