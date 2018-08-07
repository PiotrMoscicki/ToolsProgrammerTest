#pragma once

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class IHeightMapDialog : public IDialog
	{
	public:
		virtual const QPixmap* LoadHeightMap(ISceneManager* scene) = 0;
	};
}