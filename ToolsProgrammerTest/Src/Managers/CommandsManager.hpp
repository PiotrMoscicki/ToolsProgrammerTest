#pragma once

#include <vector>

#include "Managers/ICommandsManager.hpp"
#include "Structures/Commands/BlankCommand.hpp"

namespace TPT
{
	class CommandsManager : public ICommandsManager
	{
	public:
		CommandsManager() { Commands.push_back(std::move(std::make_unique<BlankCommand>())); }

		void AddCommand(std::unique_ptr<ICommand> cmd) override;

		void Undo() override;
		void Redo() override;

	private:
		bool InitialCommand = true;
		size_t CommandIdx = 0;
		std::vector<std::unique_ptr<ICommand>> Commands;
	};
}