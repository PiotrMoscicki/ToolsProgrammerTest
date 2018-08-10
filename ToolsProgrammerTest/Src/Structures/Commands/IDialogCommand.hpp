#pragma once

#include "Structures/Commands/ICommand.hpp"

namespace TPT
{
	class IInspectorManager;

	class IDialogCommand : public ICommand
	{
	public:
		virtual void SetInspectorManager(IInspectorManager* inspectorManager) = 0;
	};
}