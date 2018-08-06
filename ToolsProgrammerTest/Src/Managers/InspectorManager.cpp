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
	emit PointSpawnedSignal(point);
}

// ************************************************************************************************
void Inspectormanager::DestroyPoint()
{
	emit PointDestroyedSignal(ProjectManager->GetSceneManager()->GetScene()->GetPointById(SelectedPoint->Id));
	ProjectManager->GetSceneManager()->DestroyPoint(SelectedPoint->Id);
	SelectedPoint = nullptr;
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
void Inspectormanager::ModifyPoint(std::unique_ptr<IPointModificationCommand> cmd)
{
	cmd->SetPoint(SelectedPoint);
	cmd->Execute();
}
