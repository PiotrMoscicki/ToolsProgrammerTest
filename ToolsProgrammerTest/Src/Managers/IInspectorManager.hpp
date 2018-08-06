#pragma once

#include <QtCore/qobject.h>

#include "Managers/Dialogs/IPointDialog.hpp"
#include "Inspectors/IInspector.hpp"
#include "Structures/Scene.hpp"
#include "Structures/Commands/IPointModificationCommand.hpp"

namespace TPT
{
	class IProjectManager;

	class IInspectorManager : public QObject
	{
		Q_OBJECT

	public:
		virtual void SetProjectManager(IProjectManager* projectManager) = 0;
		virtual void SetPointDialog(std::unique_ptr<IPointDialog> pointDialog) = 0;

		virtual void AddInspector(std::unique_ptr<IInspector> inspector) = 0;


		virtual const QPixmap* GetHeightMap() = 0;
		virtual const std::vector<Point*>& GetPoints() = 0;
		virtual const Point* GetSelectedPoint() = 0;


		// Displays PointDialog in creation mode.
		virtual void SpawnPoint() = 0;
		// Displays PointDialog in destruction mode.
		virtual void DestroyPoint() = 0;
		// Sets currently selected point to given.
		virtual void SelectPoint(size_t id) = 0;
		// Deselects currently selected point.
		virtual void DeselectPoint() = 0;
		// modifies point and adds cmd to undo/redo stack.
		virtual void ModifyPoint(std::unique_ptr<IPointModificationCommand> cmd) = 0;


		// Displays HeightMapDialog and replaces old height map in scene object.
		virtual void LoadHeightMap() = 0;

	public slots:
		virtual void HeightMapLoaded() = 0;

	signals:
		void HeightMapLoadedSignal(const QPixmap* heightMap);

		void PointSpawnedSignal(const Point* point);
		void PointDestroyedSignal(const Point* point);
		void PointSelectedSignal(const Point* point);
		void PointModifiedSignal(const Point* point);

		void HeightMapLoadedSignel(const QPixmap* heightMap);
	};
}