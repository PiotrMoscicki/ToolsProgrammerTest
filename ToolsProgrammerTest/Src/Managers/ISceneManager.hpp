#pragma once

#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>

#include "Structures/Scene.hpp"

namespace TPT
{
	class ISceneManager
	{
	public:
		virtual void SetHeightMap(std::unique_ptr<QPixmap> heightMap) = 0;
		virtual QPixmap* GetHeightMap() = 0;

		virtual void SetScene(std::unique_ptr<Scene> scene) = 0;
		virtual Scene* GetScene() = 0;

		virtual Point* SpawnPoint() = 0;
		virtual Point* SpawnPoint(size_t id) = 0;
		virtual void DestroyPoint(size_t id) = 0;
	};
}