#pragma once

#include "Structures/Commands/IDialogCommand.hpp"

namespace TPT
{
	class ISceneManager;
	class IInspectorManager;

	class DestroyPointCommand : public IDialogCommand
	{
	public:
		DestroyPointCommand(size_t pointId, ISceneManager* sceneManager)
			: PointId(pointId), SceneManager(sceneManager) {}

		void Execute() override;
		void Undo() override;
		void Redo() override;

		void SetInspectorManager(IInspectorManager* inspectorManager) override { InspectorManager = inspectorManager; }

	private:
		size_t PointId;

		ISceneManager* SceneManager;
		IInspectorManager* InspectorManager;
	};
}