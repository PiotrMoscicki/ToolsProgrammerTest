#pragma once

namespace TPT
{
	class IDialog
	{
	public:
		// Reset will allow usage of one dialog instance multiple times.
		virtual void Reset() = 0;

		// If dialog was canceled by user this function returns true.
		virtual bool Canceled() = 0;;
	};
}