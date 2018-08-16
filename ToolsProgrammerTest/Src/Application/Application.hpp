#pragma once

#include <QtWidgets/qapplication.h>
#include <QtWidgets/qmainwindow.h>

#include "Dialogs/HelpDialog.hpp"

class QMenuBar;
class QMenu;
class QAction;
class QObject;
class QEvent;

namespace TPT
{
	class IProjectManager;
	class IInspectorManager;
	class ICommandsManager;

	class Application : public QApplication
	{
		Q_OBJECT

	public:
		Application(int argc, char *argv[]);

		bool eventFilter(QObject* watched, QEvent* event) override;

	private:
		QMenuBar* MenuBar;
			QMenu* EditMenu;
				QAction* UndoAction;
				QAction* RedoAction;
			QMenu* MapMenu;
				QAction* ChangeResolutionAction;
			QAction* HelpAction;

		std::unique_ptr<QMainWindow> MainWindow;
		std::unique_ptr<HelpDialog> HelpDialog;
		IProjectManager* ProjectManager;
		IInspectorManager* InspectorManager;
		ICommandsManager* CommandsManager;

		bool CtrlPressed = false;
		bool ShiftPressed = false;
		bool ZPressed = false;
		bool DuringEvent = false;

	private slots:
		void ChangeResolution();
		void Undo();
		void Redo();
		void Help();
	};

	extern Application* gApp;
}
