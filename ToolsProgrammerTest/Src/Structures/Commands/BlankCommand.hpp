#pragma once

#include "Structures/Commands/ICommand.hpp"

namespace TPT
{
	class BlankCommand : public ICommand
	{
	public:
		void Execute() override {}
		void Undo() override {}
		void Redo() override {}
	};
}