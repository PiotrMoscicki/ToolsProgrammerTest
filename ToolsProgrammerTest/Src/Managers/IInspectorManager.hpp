#pragma once

#include <QtCore/qobject.h>
#include <QtGui/qvector3d.h>

#include "Managers/Dialogs/IPointDialog.hpp"
#include "Inspectors/IInspector.hpp"

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


		virtual QVector3D* GetSelectedPoint() = 0;


		// Displays PointDialog in creation mode.
		virtual QVector3D* SpawnPoint() = 0;
		// Displays PointDialog in destruction mode.
		virtual void Destroypoint() = 0;
		// Sets currently selected point to given.
		virtual void SelectPoint(QVector3D* point) = 0;
		// modifies point and adds cmd to undo/redo stack.
		virtual void ModifyPoint() = 0;

	public slots:
		virtual void HeightMapLoaded() = 0;

	signals:
		void HeightMapLoadedSignal();

		void PointSpawnedSignal(QVector3D* point);
		void PointDestroyedSignal();
		void PointSelectedSignal(QVector3D* point);
		void PointModifiedSignal(QVector3D* point);
	};
}