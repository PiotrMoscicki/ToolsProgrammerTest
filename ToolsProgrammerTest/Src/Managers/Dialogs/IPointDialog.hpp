#pragma once

#include <vector>

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class IPointDialog : public IDialog
	{
	public:
		virtual std::vector<Point*> SpawnPoints(ISceneManager* scene) = 0;
		virtual void DestroyPoint(ISceneManager* scene, size_t id) = 0;
	};
}