#pragma once

#include <memory>

#include "Dialogs/IDialog.hpp"
#include "Structures/Commands/IDialogCommand.hpp"

namespace TPT
{
	class ISceneManager;

	class IHeightMapDialog : public IDialog
	{
	public:
		virtual std::unique_ptr<IDialogCommand> LoadHeightMap(ISceneManager* scene) = 0;
	};
}