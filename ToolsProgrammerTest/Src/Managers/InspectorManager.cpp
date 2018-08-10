#include "InspectorManager.hpp"

#include "Managers/IProjectManager.hpp"
#include "Managers/ICommandsManager.hpp"

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



//		modification functions
// ************************************************************************************************
void InspectorManager::SpawnPoint()
{
	auto cmd = PointDialog->SpawnPoints(SceneManager);

	cmd->SetInspectorManager(this);
	CommandsManager->AddCommand(std::move(cmd));

	PointDialog->Reset();
}

// ************************************************************************************************
void InspectorManager::DestroyPoint()
{
	if (!SelectedPoint)
		return;

	auto cmd = PointDialog->DestroyPoint(SceneManager, SelectedPoint->Id);

	cmd->SetInspectorManager(this);
	CommandsManager->AddCommand(std::move(cmd));

	DeselectPoint();
}

// ************************************************************************************************
void InspectorManager::SelectPoint(size_t id)
{
	SelectedPoint = SceneManager->GetPoint(id);
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
	CommandsManager->AddCommand(std::move(cmd));
}

// ************************************************************************************************
void InspectorManager::LoadHeightMap()
{
	auto cmd = HeightMapDialog->LoadHeightMap(SceneManager);

	if (HeightMapDialog->Canceled())
		return;

	cmd->SetInspectorManager(this);
	CommandsManager->AddCommand(std::move(cmd));

	HeightMapDialog->Reset();
}

// ************************************************************************************************
void InspectorManager::ChangeSceneResolution()
{
	auto oldResolution = SceneManager->GetSceneResolution();
	auto cmd = SceneResolutionDialog->SetSceneResolution(SceneManager);

	if (SceneResolutionDialog->Canceled())
		return;

	cmd->SetInspectorManager(this);
	CommandsManager->AddCommand(std::move(cmd));

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
