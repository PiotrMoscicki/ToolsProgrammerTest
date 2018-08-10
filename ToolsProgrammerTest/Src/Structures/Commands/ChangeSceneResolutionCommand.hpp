#pragma once

#include "Structures/Commands/IDialogCommand.hpp"
#include "Managers/IInspectorManager.hpp"

namespace TPT
{
	class ChangeSceneResolutionCommand : public IDialogCommand
	{
	public:
		ChangeSceneResolutionCommand(SceneResolution undoValue, SceneResolution redoValue, ISceneManager* sceneManager)
			: UndoValue(undoValue), RedoValue(redoValue), SceneManager(sceneManager) {}

		void Execute() override;
		void Undo() override;
		void Redo() override;

		void SetInspectorManager(IInspectorManager* inspectorManager) override { InspectorManager = inspectorManager; }

	private:
		SceneResolution UndoValue;
		SceneResolution RedoValue; 

		ISceneManager* SceneManager;
		IInspectorManager* InspectorManager;
	};
}