#pragma once

#include <QtWidgets/qapplication.h>
#include <QtCore/qtimer.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qmenubar.h>

#include "Managers/IProjectManager.hpp"

namespace TPT
{
	class Application : public QApplication
	{
		Q_OBJECT

	public:
		Application(int argc, char *argv[]);

	private:
		QMenuBar* MenuBar;
			QMenu* MapMenu;
				QAction* ChangeResolutionAction;

		std::unique_ptr<QMainWindow> MainWindow;
		std::unique_ptr<IProjectManager> ProjectManager;

	private slots:
		void ChangeResolution();
	};

	extern Application* gApp;
}
