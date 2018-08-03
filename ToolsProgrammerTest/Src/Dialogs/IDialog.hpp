#pragma once

namespace TPT
{
	class IDialog
	{
		// Reset will allow usage of one dialog instance multiple times.
		virtual void Reset() = 0;

		// If dialog was canceled by user this function returns true.
		virtual bool Canceled() = 0;;
	};
}