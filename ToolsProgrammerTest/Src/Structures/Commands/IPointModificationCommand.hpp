#pragma once

#include "Structures/Commands/ICommand.hpp"
#include "Structures/Point.hpp"
#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class IPointModificationCommand : public ICommand
	{
	public:
		virtual size_t GetPointId() = 0;
		virtual void SetSceneManager(ISceneManager* sceneManager) = 0;
	};
}