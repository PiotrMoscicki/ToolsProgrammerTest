#include "PointModificationCommand.hpp"

#include "Managers/IInspectorManager.hpp"

using namespace TPT;

// ************************************************************************************************
void PointModificationCommand::Execute()
{
	auto point = SceneManager->GetPoint(PointId);
	*point = RedoValue;

	if (SceneManager->GetHeightMap())
		point->PosY = QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

	Manager->PointModifiedSignal(point);
}

// ************************************************************************************************
void PointModificationCommand::Undo()
{
	auto point = SceneManager->GetPoint(PointId);
	*point = UndoValue;

	if (SceneManager->GetHeightMap())
		point->PosY = QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

	Manager->PointModifiedSignal(point);
}

// ************************************************************************************************
void PointModificationCommand::Redo()
{
	auto point = SceneManager->GetPoint(PointId);
	*point = RedoValue;

	if (SceneManager->GetHeightMap())
		point->PosY = QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

	Manager->PointModifiedSignal(point);
}
