#pragma once

namespace TPT
{
	class IInspectorManager;

	class IInspector
	{
	public:
		virtual void SetManager(IInspectorManager* manager) = 0;
	};
}