#include "InspectorManager.hpp"

#include "Managers/IProjectManager.hpp"

using namespace TPT;

// ************************************************************************************************
InspectorManager::InspectorManager()
{
	connect(this, &InspectorManager::HeightMapLoadedSignal, this, &InspectorManager::HeightMapLoaded);
	connect(this, &InspectorManager::SceneResolutionChangedSignal, this, &InspectorManager::SceneResolutionChanged);
}

// ************************************************************************************************
const QPixmap* InspectorManager::GetHeightMap()
{
	return SceneManager->GetHeightMap();
}

// ************************************************************************************************
const std::vector<Point*>& InspectorManager::GetPoints()
{
	return SceneManager->GetPoints();
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
			float denominator = 1.f / 255 * SceneManager->GetSceneResolution().Y;

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

	emit PointDestroyedSignal(SceneManager->GetPoint(SelectedPoint->Id));
	SceneManager->DestroyPoint(SelectedPoint->Id);

	DeselectPoint();
}

// ************************************************************************************************
void InspectorManager::SelectPoint(size_t id)
{
	auto points = SceneManager->GetPoints();

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
	auto point = SceneManager->GetPoint(cmd->GetPointId());

	cmd->SetSceneManager(SceneManager);
	cmd->Execute();
	cmd.release();

	if (SceneManager->GetHeightMap())
		point->PosY = QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

	emit PointModifiedSignal(point);
}

// ************************************************************************************************
void InspectorManager::LoadHeightMap()
{
	auto heightMap = HeightMapDialog->LoadHeightMap(SceneManager);
	if (!HeightMapDialog->Canceled())
		emit HeightMapLoadedSignal(heightMap);

	HeightMapDialog->Reset();
}

void InspectorManager::ChangeSceneResolution()
{
	auto oldResolution = SceneManager->GetSceneResolution();
	auto cmd = SceneResolutionDialog->SetSceneResolution(SceneManager);

	cmd->SetInspectorManager(this);
	cmd->Execute();
	cmd.release();

	if (!SceneResolutionDialog->Canceled())
		emit SceneResolutionChangedSignal(SceneManager->GetSceneResolution(), oldResolution);

	SceneResolutionDialog->Reset();
}




//		private slots
// ************************************************************************************************
void InspectorManager::HeightMapLoaded(const QPixmap* heightMap)
{
	auto hm = heightMap->toImage();
	auto y = (float)SceneManager->GetSceneResolution().Y / 255;

	for (auto point : SceneManager->GetPoints())
	{
		point->PosY = y * QColor(hm.pixel(point->PosX, point->PosZ)).value();

		emit PointModifiedSignal(point);
	}
}

// ************************************************************************************************
void InspectorManager::SceneResolutionChanged(SceneResolution resolution, SceneResolution oldResolution)
{
	auto x = (float)resolution.X / oldResolution.X;
	auto y = (float)resolution.Y / oldResolution.Y;
	auto Z = (float)resolution.Z / oldResolution.Z;

	for (auto point : SceneManager->GetPoints())
	{
		point->PosX *= x;
		point->PosY *= y;
		point->PosZ *= Z;

		emit PointModifiedSignal(point);
	}
}
