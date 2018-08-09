#include "SceneManager.hpp"

using namespace TPT;

void SceneManager::SetHeightMap(std::unique_ptr<QPixmap> heightMap)
{
	HeightMap = std::move(heightMap);
}

// ************************************************************************************************
Point* SceneManager::SpawnPoint()
{
	auto newPoint = new Point();
	Points.push_back(newPoint);

	return newPoint;
}

// ************************************************************************************************
Point* SceneManager::SpawnPoint(size_t id)
{
	auto newPoint = new Point(id);
	Points.push_back(newPoint);

	return newPoint;
}

// ************************************************************************************************
void SceneManager::DestroyPoint(size_t id)
{
	for (auto i = 0; i < Points.size(); ++i)
		if (Points[i]->Id == id)
		{
			Points.erase(Points.begin() + i);
			break;
		}
}

// ************************************************************************************************
Point* SceneManager::GetPoint(size_t id)
{
	for (auto point : Points)
		if (point->Id == id)
			return point;

	throw new std::exception;
}
