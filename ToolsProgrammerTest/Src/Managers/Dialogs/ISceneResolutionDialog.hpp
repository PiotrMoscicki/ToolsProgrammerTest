#pragma once

#include "Dialogs/IDialog.hpp"
#include "Managers/ISceneManager.hpp"
#include "Structures/SceneResolution.hpp"

namespace TPT
{
	class ISceneResolutionDialog : public IDialog
	{
	public:
		virtual SceneResolution SetSceneResolution(ISceneManager* scene) = 0;
	};
}