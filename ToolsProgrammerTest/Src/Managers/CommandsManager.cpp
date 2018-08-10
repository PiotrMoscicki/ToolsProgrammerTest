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
	Commands.resize(CommandIdx + 1);
	Commands.push_back(std::move(cmd));
	
	LastCommandType = eCommandType::EXECUTE;
	++CommandIdx;
}

// ************************************************************************************************
void CommandsManager::Undo()
{
	if (CommandIdx == 0 && LastCommandType == eCommandType::UNDO)
		++CommandIdx;

	Commands[CommandIdx]->Undo();

	if (LastCommandType == eCommandType::UNDO)
		--CommandIdx;
	LastCommandType = eCommandType::UNDO;
}

// ************************************************************************************************
void CommandsManager::Redo()
{
	if (CommandIdx == Commands.size() - 1 && LastCommandType == eCommandType::REDO)
		return;

	Commands[CommandIdx]->Redo();

	if (LastCommandType == eCommandType::REDO)
		++CommandIdx;
	LastCommandType = eCommandType::REDO;
}
