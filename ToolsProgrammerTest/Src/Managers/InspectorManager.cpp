#include "InspectorManager.hpp"

#include "Managers/IProjectManager.hpp"

using namespace TPT;

// ************************************************************************************************
const QPixmap* InspectorManager::GetHeightMap()
{
	return SceneManager->GetHeightMap();
}

// ************************************************************************************************
const std::vector<Point*>& InspectorManager::GetPoints()
{
	return SceneManager->GetScene()->Points;
}

// ************************************************************************************************
void InspectorManager::SpawnPoint()
{
	auto points = PointDialog->SpawnPoints(SceneManager);

	if (!PointDialog->Canceled())
	{
		if (SceneManager->GetHeightMap())
		{
			auto heightMap = SceneManager->GetHeightMap()->toImage();
			float denominator = 1.f / 255 * SceneManager->GetScene()->ResolutionY;

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

	emit PointDestroyedSignal(SceneManager->GetScene()->GetPointById(SelectedPoint->Id));
	SceneManager->DestroyPoint(SelectedPoint->Id);

	DeselectPoint();
}

// ************************************************************************************************
void InspectorManager::SelectPoint(size_t id)
{
	auto points = SceneManager->GetScene()->Points;

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
	auto point = SceneManager->GetScene()->GetPointById(cmd->GetPointId());

	cmd->SetSceneManager(SceneManager);
	cmd->Execute();
	cmd.release();

	point->PosY = QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

	emit PointModifiedSignal(point);
}

// ************************************************************************************************
void InspectorManager::LoadHeightMap()
{
	auto heightMap = HeightMapDialog->LoadHeightMap(SceneManager);
	if (!HeightMapDialog->Canceled())
	{
		emit HeightMapLoadedSignal(heightMap);

		auto hm = heightMap->toImage();

		for (auto point : SceneManager->GetScene()->Points)
		{
			point->PosY = QColor(hm.pixel(point->PosX, point->PosZ)).value();

			emit PointModifiedSignal(point);
		}
	}

	HeightMapDialog->Reset();
}
