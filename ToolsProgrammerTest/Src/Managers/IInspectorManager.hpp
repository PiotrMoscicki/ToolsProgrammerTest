#pragma once

#include <QtCore/qobject.h>

#include "Managers/Dialogs/IPointDialog.hpp"
#include "Managers/Dialogs/IHeightMapDialog.hpp"
#include "Managers/Dialogs/ISceneResolutionDialog.hpp"
#include "Inspectors/IInspector.hpp"
#include "Structures/Commands/IPointModificationCommand.hpp"
#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class IProjectManager;
	class ISceneManager;
	class ICommandsManager;
	class Point;

	class IInspectorManager : public QObject
	{
		Q_OBJECT

	public:
		virtual void SetSceneManager(ISceneManager* sceneManager) = 0;
		virtual void SetCommandsManager(ICommandsManager* commandsManager) = 0;
		virtual void SetPointDialog(std::unique_ptr<IPointDialog> pointDialog) = 0;
		virtual void SetHeightMapDialog(std::unique_ptr<IHeightMapDialog> heightMapDialog) = 0;
		virtual void SetSceneResolutionDialog(std::unique_ptr<ISceneResolutionDialog> sceneResolutionDialog) = 0;

		virtual void AddInspector(std::unique_ptr<IInspector> inspector) = 0;


		virtual SceneResolution GetSceneResolution() = 0;
		virtual const QPixmap* GetHeightMap() = 0;
		virtual const std::vector<Point*>& GetPoints() = 0;
		virtual const Point* GetSelectedPoint() = 0;


		virtual void SpawnPoint() = 0;
		virtual void DestroyPoint() = 0;
		virtual void SelectPoint(size_t id) = 0;
		virtual void DeselectPoint() = 0;
		virtual void ModifyPoint(std::unique_ptr<IPointModificationCommand> cmd) = 0;

		virtual void LoadHeightMap() = 0;
		virtual void ChangeSceneResolution() = 0;

	signals:
		void PointSpawnedSignal(const Point* point);
		void PointDestroyedSignal(const Point* point);
		void PointSelectedSignal(const Point* point);
		void PointModifiedSignal(const Point* point);

		void HeightMapLoadedSignal(const QPixmap* heightMap);
		void SceneResolutionChangedSignal(SceneResolution resolution, SceneResolution oldResolution);
	};
}