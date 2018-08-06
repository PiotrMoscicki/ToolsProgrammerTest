#pragma once

namespace TPT
{
	class ICommand
	{
	public:
		virtual void Execute() = 0;
		virtual void Undo() = 0;
		virtual void Redo() = 0;
	};
}