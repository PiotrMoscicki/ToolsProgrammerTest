#pragma once

#include <QtGui/qpixmap.h>

#include "Structures/Commands/IDialogCommand.hpp"
#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class ChangeHeightMapCommand : public IDialogCommand
	{
	public:
		ChangeHeightMapCommand(std::unique_ptr<QPixmap> undoValue, std::unique_ptr<QPixmap> redoValue, ISceneManager* sceneManager)
			: UndoValue(std::move(undoValue)), RedoValue(std::move(redoValue)), SceneManager(sceneManager) {}

		void Execute() override;
		void Undo() override;
		void Redo() override;

		void SetInspectorManager(IInspectorManager* inspectorManager) override { InspectorManager = inspectorManager; }

	private:
		std::unique_ptr<QPixmap> UndoValue;
		std::unique_ptr<QPixmap> RedoValue;

		ISceneManager* SceneManager;
		IInspectorManager* InspectorManager;
	};
}