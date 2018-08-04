#pragma once

#include "Dialogs/IDialog.hpp"
#include "Structures/Scene.hpp"

namespace TPT
{
	class IPointDialog : IDialog
	{
	public:
		// Spawns new point to given scene and terurns its pointer
		virtual const Point* SpawnPoint(Scene* scene) = 0;
		// Destroys selected pointer from given scene
		virtual void DestroyPoint(Scene* scene, size_t id) = 0;
	};
}