#pragma once

#include <vector>

#include "Dialogs/IDialog.hpp"
#include "Structures/Commands/DestroyPointCommand.hpp"
#include "Structures/Commands/SpawnPointsCommand.hpp"

namespace TPT
{
	class ISceneManager;
	class Point;

	class IPointDialog : public IDialog
	{
	public:
		virtual std::unique_ptr<SpawnPointsCommand> SpawnPoints(ISceneManager* scene) = 0;
		virtual std::unique_ptr<DestroyPointCommand> DestroyPoint(ISceneManager* scene, size_t id) = 0;
	};
}