#include "Pch.hpp"


#include "ChangeSceneResolutionCommand.hpp"

#include "Managers/IInspectorManager.hpp"

using namespace TPT;

// ************************************************************************************************
void ChangeSceneResolutionCommand::Execute()
{
	auto oldResolution = SceneManager->GetSceneResolution();
	SceneManager->SetSceneResolution(RedoValue);
	InspectorManager->SceneResolutionChangedSignal(RedoValue, oldResolution);
}

// ************************************************************************************************
void ChangeSceneResolutionCommand::Undo()
{
	auto oldResolution = SceneManager->GetSceneResolution();
	SceneManager->SetSceneResolution(UndoValue);
	InspectorManager->SceneResolutionChangedSignal(UndoValue, oldResolution);
}

// ************************************************************************************************
void ChangeSceneResolutionCommand::Redo()
{
	auto oldResolution = SceneManager->GetSceneResolution();
	SceneManager->SetSceneResolution(RedoValue);
	InspectorManager->SceneResolutionChangedSignal(RedoValue, oldResolution);
}
