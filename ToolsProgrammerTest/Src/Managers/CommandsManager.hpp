#pragma once

#include <vector>

#include "Managers/ICommandsManager.hpp"
#include "Structures/Commands/BlankCommand.hpp"

namespace TPT
{
	enum class eCommandType
	{
		EXECUTE,
		UNDO,
		REDO
	};

	class CommandsManager : public ICommandsManager
	{
	public:
		CommandsManager();

		void Execute(std::unique_ptr<ICommand> cmd) override;

		void Undo() override;
		void Redo() override;

	private:
		size_t CommandIdx = 0;
		
		std::vector<std::unique_ptr<ICommand>> Commands;
	};
}