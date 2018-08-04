#pragma once

#include <QtCore/qstring.h>

#include "Structures/Scene.hpp"

namespace TPT
{
	class ISceneManager
	{
	public:
		virtual void SetGeightMap(std::unique_ptr<QImage> heightMap) = 0;
		virtual QImage* GetHeightMap() = 0;

		virtual void SetScene(std::unique_ptr<Scene> scene) = 0;
		virtual Scene* GetScene() = 0;
	};
}