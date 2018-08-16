#pragma once

#include <memory>

#include "Structures/Commands/ICommand.hpp"

namespace TPT
{
	class ICommandsManager
	{
	public:
		virtual void Execute(std::unique_ptr<ICommand> cmd) = 0;

		virtual void Undo() = 0;
		virtual void Redo() = 0;
	};
}