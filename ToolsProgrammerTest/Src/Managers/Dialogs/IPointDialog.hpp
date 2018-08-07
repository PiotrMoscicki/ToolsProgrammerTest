#pragma once

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class IPointDialog : IDialog
	{
	public:
		// Spawns new point to given scene and terurns its pointer
		virtual const Point* SpawnPoint(ISceneManager* scene) = 0;
		// Destroys selected pointer from given scene
		virtual void DestroyPoint(ISceneManager* scene, size_t id) = 0;
	};
}