#pragma once

#include <vector>

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class IPointDialog : public IDialog
	{
	public:
		// Spawns new point to given scene and terurns its pointer
		virtual std::vector<const Point*> SpawnPoints(ISceneManager* scene) = 0;
		// Destroys selected pointer from given scene
		virtual void DestroyPoint(ISceneManager* scene, size_t id) = 0;
	};
}