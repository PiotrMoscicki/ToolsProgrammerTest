#include "ChangeHeightMapCommand.hpp"

using namespace TPT;

// ************************************************************************************************
void ChangeHeightMapCommand::Execute()
{
	auto val = std::make_unique<QPixmap>(*RedoValue);
	SceneManager->SetHeightMap(std::move(val));
}

// ************************************************************************************************
void ChangeHeightMapCommand::Undo()
{
	if (!UndoValue)
		return;

	auto val = std::make_unique<QPixmap>(*UndoValue);
	SceneManager->SetHeightMap(std::move(val));
}

// ************************************************************************************************
void ChangeHeightMapCommand::Redo()
{
	auto val = std::make_unique<QPixmap>(*RedoValue);
	SceneManager->SetHeightMap(std::move(val));
}
