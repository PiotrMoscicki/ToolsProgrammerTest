#include "PointModificationCommand.hpp"

using namespace TPT;

// ************************************************************************************************
void PointModificationCommand::Execute()
{
	auto point = SceneManager->GetScene()->GetPointById(PointId);
	*point = RedoValue; 
	Manager->PointModifiedSignal(point);
}

// ************************************************************************************************
void PointModificationCommand::Undo()
{
	auto point = SceneManager->GetScene()->GetPointById(PointId);
	*point = UndoValue;
	Manager->PointModifiedSignal(point);
}

// ************************************************************************************************
void PointModificationCommand::Redo()
{
	auto point = SceneManager->GetScene()->GetPointById(PointId);
	*point = RedoValue;
	Manager->PointModifiedSignal(point);
}
