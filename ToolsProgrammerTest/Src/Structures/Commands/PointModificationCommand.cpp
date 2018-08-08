#include "PointModificationCommand.hpp"

using namespace TPT;

// ************************************************************************************************
void PointModificationCommand::Execute()
{
	auto point = SceneManager->GetPoint(PointId);
	*point = RedoValue; 
	Manager->PointModifiedSignal(point);
}

// ************************************************************************************************
void PointModificationCommand::Undo()
{
	auto point = SceneManager->GetPoint(PointId);
	*point = UndoValue;
	Manager->PointModifiedSignal(point);
}

// ************************************************************************************************
void PointModificationCommand::Redo()
{
	auto point = SceneManager->GetPoint(PointId);
	*point = RedoValue;
	Manager->PointModifiedSignal(point);
}
