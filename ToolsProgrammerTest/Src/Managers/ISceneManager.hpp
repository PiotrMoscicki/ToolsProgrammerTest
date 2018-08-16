#pragma once

#include <QtCore/qobject.h>
#include <QtGui/qpixmap.h>

#include "Structures/SceneResolution.hpp"

namespace TPT
{
	class Point;

	class ISceneManager : public QObject
	{
		Q_OBJECT

	public:
		virtual void SetHeightMap(std::unique_ptr<QPixmap> heightMap) = 0;
		virtual QPixmap* GetHeightMap() = 0;

		virtual Point* SpawnPoint() = 0;
		virtual Point* SpawnPoint(size_t id) = 0;
		virtual void DestroyPoint(size_t id) = 0;
		virtual Point* GetPoint(size_t id) = 0;
		virtual std::vector<Point*> GetPoints() = 0;

		virtual void SetSceneResolution(SceneResolution Resolution) = 0;

		virtual SceneResolution GetSceneResolution() = 0;
	
	signals:
		void SceneResolutionChangedSignal();
	};
}