#pragma once

#include "Dialogs/IDialog.hpp"

namespace TPT
{
	class IPointDialog : IDialog
	{
	public:
		// Spawns new point to given scene and terurns its pointer
		virtual QVector3D* SpawnPoint(Scene* scene) = 0;
		// Destroys selected pointer from given scene
		virtual void DestroyPoint(Scene* scene, QVector3D* point) = 0;
	};
}