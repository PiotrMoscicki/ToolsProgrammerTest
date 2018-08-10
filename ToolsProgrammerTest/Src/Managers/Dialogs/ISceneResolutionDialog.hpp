#pragma once

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"
#include "Structures/Commands/IDialogCommand.hpp"

namespace TPT
{
	class ISceneResolutionDialog : public IDialog
	{
	public:
		virtual std::unique_ptr<IDialogCommand> SetSceneResolution(ISceneManager* scene) = 0;
	};
}