#include "SceneManager.hpp"

using namespace TPT;

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
