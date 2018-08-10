#pragma once

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"
#include "Structures/Commands/IDialogCommand.hpp"

namespace TPT
{
	class IHeightMapDialog : public IDialog
	{
	public:
		virtual std::unique_ptr<IDialogCommand> LoadHeightMap(ISceneManager* scene) = 0;
	};
}