#pragma once

#include "Managers/Dialogs/IHeightMapDialog.hpp"

namespace TPT
{
	class HeightMapDialog : public IHeightMapDialog
	{
	public:
		std::unique_ptr<ChangeHeightMapCommand> LoadHeightMap(ISceneManager* scene) override;

		void Reset() override;
		bool Canceled() override { return CanceledFlag; }

	private:
		bool CanceledFlag = true;
	};
}