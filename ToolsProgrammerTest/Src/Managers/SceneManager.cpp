#include "SceneManager.hpp"

using namespace TPT;

// ************************************************************************************************
const Point* TPT::SceneManager::SpawnPoint()
{
	auto newPoint = new Point();
	Scene->Points.insert(std::pair<size_t, Point*>(newPoint->Id, newPoint));

	return newPoint;
}

// ************************************************************************************************
const Point* TPT::SceneManager::SpawnPoint(size_t id)
{
	auto newPoint = new Point(id);
	Scene->Points.insert(std::pair<size_t, Point*>(newPoint->Id, newPoint));

	return newPoint;
}

// ************************************************************************************************
void SceneManager::DestroyPoint(size_t id)
{
	for (auto i = 0; i < Scene->Points.size(); ++i)
		if (Scene->Points[i]->Id == id)
		{
			Scene->Points.erase(Scene->Points.begin() + i);
			break;
		}
}
