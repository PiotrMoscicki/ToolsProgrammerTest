#include "Pch.hpp"


#include "ChangeHeightMapCommand.hpp"

#include "Managers/IInspectorManager.hpp"

using namespace TPT;

// ************************************************************************************************
void ChangeHeightMapCommand::Execute()
{
	auto val = std::make_unique<QPixmap>(*RedoValue);
	auto ptr = val.get();
	SceneManager->SetHeightMap(std::move(val));
	InspectorManager->HeightMapLoadedSignal(ptr);
}

// ************************************************************************************************
void ChangeHeightMapCommand::Undo()
{
	if (!UndoValue)
		return;

	auto val = std::make_unique<QPixmap>(*UndoValue);
	auto ptr = val.get();
	SceneManager->SetHeightMap(std::move(val));
	InspectorManager->HeightMapLoadedSignal(ptr);
}

// ************************************************************************************************
void ChangeHeightMapCommand::Redo()
{
	auto val = std::make_unique<QPixmap>(*RedoValue);
	auto ptr = val.get();
	SceneManager->SetHeightMap(std::move(val));
	InspectorManager->HeightMapLoadedSignal(ptr);
}
