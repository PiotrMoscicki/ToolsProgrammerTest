#include "CommandsManager.hpp"

using namespace TPT;

// ************************************************************************************************
CommandsManager::CommandsManager()
{
	Commands.push_back(std::move(std::make_unique<BlankCommand>()));
	Commands.push_back(std::move(std::make_unique<BlankCommand>()));
	CommandIdx = 1;
}

// ************************************************************************************************
void CommandsManager::AddCommand(std::unique_ptr<ICommand> cmd)
{
	cmd->Execute();

	++CommandIdx;
	Commands.resize(CommandIdx);
	Commands.push_back(std::move(cmd));
	
}

// ************************************************************************************************
void CommandsManager::Undo()
{
	Commands[CommandIdx]->Undo();

	if (CommandIdx == 0)
		return;

	--CommandIdx;
}

// ************************************************************************************************
void CommandsManager::Redo()
{
	if (CommandIdx == Commands.size() - 1)
		return;

	++CommandIdx;

	Commands[CommandIdx]->Redo();
}
