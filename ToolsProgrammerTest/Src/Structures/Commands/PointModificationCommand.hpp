#pragma once

#include "Structures/Commands/IPointModificationCommand.hpp"
#include "Structures/Point.hpp"

namespace TPT
{
	class IInspectorManager;

	class PointModificationCommand : public IPointModificationCommand
	{
	public:
		PointModificationCommand(Point undoValue, Point redoValue, size_t pointId, IInspectorManager* manager)
			: UndoValue(undoValue), RedoValue(redoValue), PointId(pointId), Manager(manager) {}

		void Execute() override;
		void Undo() override;
		void Redo() override;

		size_t GetPointId() override { return PointId; }
		void SetSceneManager(ISceneManager* sceneManager) override { SceneManager = sceneManager; }

	private:
		Point UndoValue;
		Point RedoValue;

		size_t PointId;
		IInspectorManager* Manager;
		ISceneManager* SceneManager;
	};
}