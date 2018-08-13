#include "SpawnPointsCommand.hpp"

#include "Managers/IInspectorManager.hpp"

using namespace TPT;

void SpawnPointsCommand::Execute()
{
	if (SinglePoint)
	{
		auto point = SceneManager->SpawnPoint();
		point->Name = Name;
		point->PosX = PositionX;
		point->PosZ = PositionZ;
		if (SceneManager->GetHeightMap())
			point->PosY = (float)SceneManager->GetSceneResolution().Y / 255 
				* QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

		PointsIds.push_back(point->Id);

		InspectorManager->PointSpawnedSignal(point);
	}
	else
	{
		float deltaX = (float)SceneResolutionX / PointsResolutionX;
		float deltaZ = (float)SceneResolutionZ / PointsResolutionZ;
		auto y = (float)SceneManager->GetSceneResolution().Y / 255;

		for (float x = 0; x <= SceneResolutionX; x += deltaX)
			for (float z = 0; z <= SceneResolutionZ; z += deltaZ)
			{
				auto point = SceneManager->SpawnPoint();
				point->PosX = x;
				point->PosZ = z;
				if (SceneManager->GetHeightMap())
					point->PosY = y * QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();
				PointsIds.push_back(point->Id);

				InspectorManager->PointSpawnedSignal(point);
			}
	}
}

void SpawnPointsCommand::Undo()
{
	if (SinglePoint)
	{
		InspectorManager->PointDestroyedSignal(SceneManager->GetPoint(PointsIds[0]));
		SceneManager->DestroyPoint(PointsIds[0]);
	}
	else
	{
		for (auto pointId : PointsIds)
		{
			InspectorManager->PointDestroyedSignal(SceneManager->GetPoint(pointId));
			SceneManager->DestroyPoint(pointId);
		}
	}
}

void SpawnPointsCommand::Redo()
{
	if (SinglePoint)
	{
		auto point = SceneManager->SpawnPoint(PointsIds[0]);
		point->Name = Name;
		point->PosX = PositionX;
		point->PosZ = PositionZ;
		if (SceneManager->GetHeightMap())
			point->PosY = (float)SceneManager->GetSceneResolution().Y / 255
			* QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

		InspectorManager->PointSpawnedSignal(point);
	}
	else
	{
		float deltaX = (float)SceneResolutionX / PointsResolutionX;
		float deltaZ = (float)SceneResolutionZ / PointsResolutionZ;
		auto y = (float)SceneManager->GetSceneResolution().Y / 255;

		auto ctr = 0;

		for (float x = 0; x <= SceneResolutionX; x += deltaX)
			for (float z = 0; z <= SceneResolutionZ; z += deltaZ)
			{
				auto point = SceneManager->SpawnPoint(PointsIds[ctr++]);
				point->PosX = x;
				point->PosZ = z;
				if (SceneManager->GetHeightMap())
					point->PosY = y * QColor(SceneManager->GetHeightMap()->toImage().pixel(point->PosX, point->PosZ)).value();

				InspectorManager->PointSpawnedSignal(point);
			}

		if (ctr != PointsIds.size())
			throw new std::exception();
	}
}