#pragma once

#include <QtCore/qstring.h>

#include "Managers/IInspectorManager.hpp"

namespace TPT
{
	class IProjectManager
	{
	public:
		virtual void SetInspectorManager(std::unique_ptr<IInspectorManager> inspectorManager) = 0;

		virtual void LoadHeightMap(const QString& path) = 0;

		virtual void GetScene();
	};
}