#include "InspectorManager.hpp"

#include "Managers/IProjectManager.hpp"

using namespace TPT;

// ************************************************************************************************
const QImage* Inspectormanager::GetHeightMap()
{
	return ProjectManager->GetSceneManager()->GetHeightMap();
}

// ************************************************************************************************
const std::vector<Point*>& Inspectormanager::GetPoints()
{
	return ProjectManager->GetSceneManager()->GetScene()->Points;
}

// ************************************************************************************************
void Inspectormanager::SpawnPoint()
{
	auto point = ProjectManager->GetSceneManager()->SpawnPoint();
	emit PointSpawnedSignal(point->Id);
}

// ************************************************************************************************
void Inspectormanager::DestroyPoint(size_t id)
{
	ProjectManager->GetSceneManager()->DestroyPoint(id);
	emit PointDestroyedSignal(id);
}

// ************************************************************************************************
void Inspectormanager::SelectPoint(size_t id)
{
	auto points = ProjectManager->GetSceneManager()->GetScene()->Points;

	for (auto point : points)
		if (point->Id == id)
		{
			SelectedPoint = point;
			break;
		}
}

// ************************************************************************************************
void Inspectormanager::ModifyPoint(size_t id, IPointModificationCommand* cmd)
{
	auto points = ProjectManager->GetSceneManager()->GetScene()->Points;

	for (auto point : points)
		if (point->Id == id)
		{
			cmd->SetPoint(point);
			cmd->Execute();
		}
}
