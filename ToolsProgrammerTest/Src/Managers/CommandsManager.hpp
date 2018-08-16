#pragma once

#include <vector>

#include "Managers/ICommandsManager.hpp"

namespace TPT
{
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