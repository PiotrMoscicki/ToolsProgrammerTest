#pragma once

#include <QtWidgets/qapplication.h>
#include <QtCore/qtimer.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qmenubar.h>

#include "Managers/IProjectManager.hpp"
#include "Managers/IInspectorManager.hpp"
#include "Managers/ICommandsManager.hpp"

namespace TPT
{
	class Application : public QApplication
	{
		Q_OBJECT

	public:
		Application(int argc, char *argv[]);

	private:
		QMenuBar* MenuBar;
			QMenu* EditMenu;
				QAction* UndoAction;
				QAction* RedoAction;
			QMenu* MapMenu;
				QAction* ChangeResolutionAction;

		std::unique_ptr<QMainWindow> MainWindow;
		IProjectManager* ProjectManager;
		IInspectorManager* InspectorManager;
		ICommandsManager* CommandsManager;

	private slots:
		void ChangeResolution();
		void Undo();
		void Redo();
	};

	extern Application* gApp;
}
