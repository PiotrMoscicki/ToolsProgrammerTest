#pragma once

#include <QtCore/qstring.h>

#include "Managers/IInspectorManager.hpp"
#include "Managers/ISceneManager.hpp"
#include "Managers/ICommandsManager.hpp"

namespace TPT
{
	class IProjectManager : public QObject
	{
		Q_OBJECT

	public:
		virtual void SetInspectorManager(std::unique_ptr<IInspectorManager> inspectorManager) = 0;
		virtual void SetSceneManager(std::unique_ptr<ISceneManager> sceneManager) = 0;
		virtual void SetCommandsManager(std::unique_ptr<ICommandsManager> commandsManager) = 0;

		virtual void LoadHeightMap(const QString& path) = 0;

		virtual ISceneManager* GetSceneManager() = 0;

	signals:
		void HeightMapLoadedSignal();
	};
}