#pragma once

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"
#include "Structures/Commands/IChangeSceneResolutionCommand.hpp"

namespace TPT
{
	class ISceneResolutionDialog : public IDialog
	{
	public:
		virtual std::unique_ptr<IChangeSceneResolutionCommand> SetSceneResolution(ISceneManager* scene) = 0;
	};
}