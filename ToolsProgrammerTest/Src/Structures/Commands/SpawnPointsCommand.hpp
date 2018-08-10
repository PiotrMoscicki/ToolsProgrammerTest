#pragma once

#include <vector>
#include <QtCore/qstring.h>

#include "Structures/Commands/IDialogCommand.hpp"

namespace TPT
{
	class ISceneManager;
	class IInspectorManager;

	class SpawnPointsCommand : public IDialogCommand
	{
	public:
		SpawnPointsCommand(QString name, size_t xPos, size_t zPos, ISceneManager* sceneManager)
			: Name(name), PositionX(xPos), PositionZ(zPos), SceneManager(sceneManager) {}

		SpawnPointsCommand(size_t pointsResolutionX, size_t pointsResolutionZ
			, size_t sceneResolutionX, size_t sceneResolutionZ, ISceneManager* sceneManager)
			: PointsResolutionX(pointsResolutionX), PointsResolutionZ(pointsResolutionZ)
			, SceneResolutionX(sceneResolutionX), SceneResolutionZ(sceneResolutionZ), SceneManager(sceneManager), SinglePoint(false) {}

		void Execute() override;
		void Undo() override;
		void Redo() override;

		void SetInspectorManager(IInspectorManager* inspectorManager) override { InspectorManager = inspectorManager; }

	private:
		bool SinglePoint = true;

		QString Name;
		size_t PositionX;
		size_t PositionZ;

		std::vector<size_t> PointsIds;
		size_t PointsResolutionX;
		size_t PointsResolutionZ;
		size_t SceneResolutionX;
		size_t SceneResolutionZ;

		ISceneManager* SceneManager;
		IInspectorManager* InspectorManager;
	};
}