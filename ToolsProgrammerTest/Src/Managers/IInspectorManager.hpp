#pragma once

#include <QtCore/qobject.h>

#include "Managers/Dialogs/IPointDialog.hpp"
#include "Inspectors/IInspector.hpp"
#include "Structures/Scene.hpp"
#include "Structures/IPointModificationCommand.hpp"

namespace TPT
{
	class IProjectManager;

	class IInspectorManager : public QObject
	{
		Q_OBJECT

	public:
		virtual void SetProjectManager(IProjectManager* projectManager);
		virtual void SetPointDialog(std::unique_ptr<IPointDialog> pointDialog) = 0;

		virtual void AddInspector(std::unique_ptr<IInspector> inspector) = 0;


		virtual const QImage* GetHeightMap() = 0;
		virtual const std::vector<Point*>& GetPoints() = 0;
		virtual const Point* GetSelectedPoint() = 0;


		// Displays PointDialog in creation mode.
		virtual void SpawnPoint() = 0;
		// Displays PointDialog in destruction mode.
		virtual void DestroyPoint(size_t id) = 0;
		// Sets currently selected point to given.
		virtual void SelectPoint(size_t id) = 0;
		// modifies point and adds cmd to undo/redo stack.
		virtual void ModifyPoint(size_t id, IPointModificationCommand* cmd) = 0;

	public slots:
		virtual void HeightMapLoaded() = 0;

	signals:
		void HeightMapLoadedSignal();

		void PointSpawnedSignal(size_t id);
		void PointDestroyedSignal(size_t id);
		void PointSelectedSignal(size_t id);
		void PointModifiedSignal(size_t id);
	};
}