#pragma once

#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>
#include <QtCore/qobject.h>

#include "Structures/Point.hpp"
#include "Structures/SceneResolution.hpp"

namespace TPT
{
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