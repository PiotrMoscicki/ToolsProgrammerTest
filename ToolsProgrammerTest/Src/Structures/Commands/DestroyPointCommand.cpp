#include "DestroyPointCommand.hpp"

#include "Managers/IInspectorManager.hpp"

using namespace TPT;

void DestroyPointCommand::Execute()
{
	InspectorManager->PointDestroyedSignal(SceneManager->GetPoint(PointId));
	SceneManager->DestroyPoint(PointId);
}

void DestroyPointCommand::Undo()
{
	SceneManager->SpawnPoint(PointId);
	InspectorManager->PointSpawnedSignal(SceneManager->GetPoint(PointId));
}

void DestroyPointCommand::Redo()
{
	InspectorManager->PointDestroyedSignal(SceneManager->GetPoint(PointId));
	SceneManager->DestroyPoint(PointId);
}
