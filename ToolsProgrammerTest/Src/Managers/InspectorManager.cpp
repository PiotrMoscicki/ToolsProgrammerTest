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
	auto points = PointDialog->SpawnPoints(ProjectManager->GetSceneManager());

	if (!PointDialog->Canceled())
	{
		if (ProjectManager->GetSceneManager()->GetHeightMap())
		{
			auto heightMap = ProjectManager->GetSceneManager()->GetHeightMap()->toImage();
			float denominator = 1.f / 255 * ProjectManager->GetSceneManager()->GetScene()->ResolutionY;

			for (auto point : points)
			{
				point->PosY = QColor(heightMap.pixel(point->PosX, point->PosZ)).value() * denominator;

				emit PointSpawnedSignal(point);
			}
		}
		else
			for (auto point : points)
				emit PointSpawnedSignal(point);
	}

	PointDialog->Reset();
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

	point->PosY = QColor(ProjectManager->GetSceneManager()->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

	emit PointModifiedSignal(point);
}

// ************************************************************************************************
void InspectorManager::LoadHeightMap()
{
	auto heightMap = HeightMapDialog->LoadHeightMap(ProjectManager->GetSceneManager());
	if (!HeightMapDialog->Canceled())
	{
		emit HeightMapLoadedSignal(heightMap);

		auto hm = heightMap->toImage();

		for (auto point : ProjectManager->GetSceneManager()->GetScene()->Points)
		{
			point->PosY = QColor(hm.pixel(point->PosX, point->PosZ)).value();

			emit PointModifiedSignal(point);
		}
	}

	HeightMapDialog->Reset();
}
