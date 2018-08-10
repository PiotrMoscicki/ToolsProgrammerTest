#include "CommandsManager.hpp"

using namespace TPT;

// ************************************************************************************************
void CommandsManager::AddCommand(std::unique_ptr<ICommand> cmd)
{
	cmd->Execute();
	Commands.push_back(std::move(cmd));
	++CommandIdx;
}

// ************************************************************************************************
void CommandsManager::Undo()
{
	if (CommandIdx == 0)
		return;

	Commands[CommandIdx]->Undo();
	--CommandIdx;
}

// ************************************************************************************************
void CommandsManager::Redo()
{
	if (CommandIdx == Commands.size() - 1)
		return;

	Commands[CommandIdx]->Redo();
	++CommandIdx;
}
