#pragma once

#include <QtCore/qobject.h>

#include "Managers/Dialogs/IPointDialog.hpp"

namespace TPT
{
	class IProjectManager;

	class IInspectorManager : public QObject
	{
		Q_OBJECT

	public:
		virtual void SetProjectManager(IProjectManager* projectManager);
		virtual void SetPointDialog(std::unique_ptr<IPointDialog> pointDialog) = 0;

		virtual void SetSceneInspector() = 0;
		virtual void SetPointInspector() = 0;
		virtual void SetTextureInspector() = 0;
		virtual void Set3DInspector() = 0;


		virtual void GetSelectedpoint() = 0;


		// Displays PointDialog in creation mode.
		virtual void SpawnPoint() = 0;
		// Displays PointDialog in destruction mode.
		virtual void Destroypoint() = 0;
		// Sets currently selected point to given.
		virtual void SelectPoint() = 0;
		// modifies point and adds cmd to undo/redo stack.
		virtual void ModifyPoint() = 0;

	signals:
		void PointSpawnedSignal();
		void PointDestroyedSignal();
		void PointSelectedSignal();
		void PointModifiedSignal();
	};
}