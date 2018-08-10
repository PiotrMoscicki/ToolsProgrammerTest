#pragma once

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"
#include "Structures/Commands/ChangeHeightMapCommand.hpp"

namespace TPT
{
	class IHeightMapDialog : public IDialog
	{
	public:
		virtual std::unique_ptr<ChangeHeightMapCommand> LoadHeightMap(ISceneManager* scene) = 0;
	};
}