#pragma once

#include <QtCore/qstring.h>

#include "Managers/IInspectorManager.hpp"
#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class IProjectManager
	{
	public:
		virtual void SetInspectorManager(std::unique_ptr<IInspectorManager> inspectorManager) = 0;
		virtual void SetSceneManager(std::unique_ptr<ISceneManager> sceneManager) = 0;

		virtual void LoadHeightMap(const QString& path) = 0;
	};
}