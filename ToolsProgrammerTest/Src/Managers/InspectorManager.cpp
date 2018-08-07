#include "InspectorManager.hpp"

#include "Managers/IProjectManager.hpp"

using namespace TPT;

// ************************************************************************************************
const QPixmap* InspectorManager::GetHeightMap()
{
	return ProjectManager->GetSceneManager()->GetHeightMap();
}

// ************************************************************************************************
const std::vector<Point*>& InspectorManager::GetPoints()
{
	return ProjectManager->GetSceneManager()->GetScene()->Points;
}

// ************************************************************************************************
void InspectorManager::SpawnPoint()
{
	auto point = ProjectManager->GetSceneManager()->SpawnPoint();
	emit PointSpawnedSignal(point);
}

// ************************************************************************************************
void InspectorManager::DestroyPoint()
{
	if (!SelectedPoint)
		return;

	emit PointDestroyedSignal(ProjectManager->GetSceneManager()->GetScene()->GetPointById(SelectedPoint->Id));
	ProjectManager->GetSceneManager()->DestroyPoint(SelectedPoint->Id);

	DeselectPoint();
}

// ************************************************************************************************
void InspectorManager::SelectPoint(size_t id)
{
	auto points = ProjectManager->GetSceneManager()->GetScene()->Points;

	for (auto point : points)
		if (point->Id == id)
		{
			SelectedPoint = point;
			break;
		}

	emit PointSelectedSignal(SelectedPoint);
}

// ************************************************************************************************
void InspectorManager::DeselectPoint()
{
	SelectedPoint = nullptr;
	emit PointSelectedSignal(SelectedPoint);
}

// ************************************************************************************************
void InspectorManager::ModifyPoint(std::unique_ptr<IPointModificationCommand> cmd)
{
	auto point = ProjectManager->GetSceneManager()->GetScene()->GetPointById(cmd->GetPointId());

	cmd->SetSceneManager(ProjectManager->GetSceneManager());
	cmd->Execute();
	cmd.release();

	emit PointModifiedSignal(point);
}

// ************************************************************************************************
void InspectorManager::LoadHeightMap()
{
	auto heightMap = HeightMapDialog->LoadHeightMap(ProjectManager->GetSceneManager());
	if (!HeightMapDialog->Canceled())
		emit HeightMapLoadedSignal(heightMap);

	HeightMapDialog->Reset();
}
