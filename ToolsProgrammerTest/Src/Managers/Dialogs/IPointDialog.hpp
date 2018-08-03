#pragma once

#include "Dialogs/IDialog.hpp"

namespace TPT
{
	class IPointDialog : IDialog
	{
	public:
		// Spawns new point to given scene and terurns its pointer
		virtual void SpawnPoint() = 0;
		// Destroys selected pointer from given scene
		virtual void DestroyPoint() = 0;
	};
}