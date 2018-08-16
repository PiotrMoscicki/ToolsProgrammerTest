#include "Application.hpp"

#include <QtWidgets/QStyleFactory>
#include <QtWidgets/qdockwidget.h>
#include <QtCore/qcoreevent.h>
#include <Qt3DInput/qkeyevent.h>

#include "Managers/InspectorManager.hpp"
#include "Managers/ProjectManager.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/CommandsManager.hpp"

#include "Inspectors/SceneInspector.hpp"
#include "Inspectors/PointInspector.hpp"
#include "Inspectors/HeightMapInspector.hpp"
#include "Inspectors/Scene3DInspector.hpp"

#include "Managers/Dialogs/PointDialog.hpp"
#include "Managers/Dialogs/HeightMapDialog.hpp"
#include "Managers/Dialogs/SceneResolutionDialog.hpp"

using namespace TPT;

// ************************************************************************************************
namespace TPT
{
	Application* gApp = nullptr;
}

// ************************************************************************************************
Application::Application(int argc, char *argv[])
	: QApplication(argc, argv), MainWindow(std::move(std::make_unique<QMainWindow>()))
{
	gApp = this;

	setStyle(QStyleFactory::create("s"));

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(45, 45, 45));
	darkPalette.setColor(QPalette::WindowText, Qt::lightGray);
	darkPalette.setColor(QPalette::Base, QColor(30, 30, 30));
	darkPalette.setColor(QPalette::AlternateBase, QColor(255, 0, 0));
	darkPalette.setColor(QPalette::ToolTipBase, QColor(40, 40, 40));
	darkPalette.setColor(QPalette::ToolTipText, Qt::lightGray);
	darkPalette.setColor(QPalette::Text, Qt::lightGray);
	darkPalette.setColor(QPalette::Button, QColor(55, 55, 55));
	darkPalette.setColor(QPalette::ButtonText, Qt::lightGray);
	darkPalette.setColor(QPalette::BrightText, QColor(255, 0, 0));

	darkPalette.setColor(QPalette::Highlight, QColor(225, 159, 4));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::LinkVisited, QColor(150, 0, 150));

	qApp->setPalette(darkPalette);

	qApp->setStyleSheet("QToolTip { color: #000000; background-color: #e19f04; border: 1px solid black; } \
						 QDockWidget { font-family: \"Bennet\" } \
						 QWidget { font-family: \"Consolas\" } \
						 QLineEdit:disabled { color: #c0c0c0; background-color: #323232; } \
						 QLineEdit { color: #c0c0c0; background-color: #404040; }");

	MainWindow->setWindowTitle("ToolsProgrammerTest Editor");
	MainWindow->setDockNestingEnabled(true);
	MainWindow->resize(1280, 720);

	// menu bar
	MenuBar = new QMenuBar(MainWindow.get());
	MainWindow->setMenuBar(MenuBar);

		// edit menu
		EditMenu = new QMenu(MainWindow.get());
		MenuBar->addAction(EditMenu->menuAction());
		EditMenu->setTitle("Edit");

			UndoAction = new QAction(MainWindow.get());
			EditMenu->addAction(UndoAction);
			UndoAction->setText("Undo");
			connect(UndoAction, &QAction::triggered, this, &Application::Undo);

			RedoAction = new QAction(MainWindow.get());
			EditMenu->addAction(RedoAction);
			RedoAction->setText("Redo");
			connect(RedoAction, &QAction::triggered, this, &Application::Redo);

		// file menu
		MapMenu = new QMenu(MainWindow.get());
		MenuBar->addAction(MapMenu->menuAction());
		MapMenu->setTitle("Map");

			ChangeResolutionAction = new QAction(MainWindow.get());
			MapMenu->addAction(ChangeResolutionAction);
			ChangeResolutionAction->setText("Change Resolution");
			connect(ChangeResolutionAction, &QAction::triggered, this, &Application::ChangeResolution);

		HelpAction = new QAction(MainWindow.get());
		MenuBar->addAction(HelpAction);
		HelpAction->setText("Help");
		connect(HelpAction, &QAction::triggered, this, &Application::Help);

	MainWindow->show();

	
	auto  widget = new QDockWidget("Scene Inspector", MainWindow.get());
	auto sceneInspector = std::make_unique<SceneInspector>(nullptr);
	widget->setWidget(sceneInspector.get());
	MainWindow->addDockWidget(Qt::LeftDockWidgetArea, widget);
	widget->setMinimumSize(300, 300);
	
	widget = new QDockWidget("Point Inspector", MainWindow.get());
	auto pointInspector = std::make_unique<PointInspector>(nullptr);
	widget->setWidget(pointInspector.get());
	MainWindow->addDockWidget(Qt::LeftDockWidgetArea, widget);
	widget->setMinimumSize(300, 0);

	widget = new QDockWidget("Height Map Inspector", MainWindow.get());
	auto heightMapInspector = std::make_unique<HeightMapInspector>(nullptr);
	widget->setWidget(heightMapInspector.get());
	MainWindow->addDockWidget(Qt::LeftDockWidgetArea, widget);
	widget->setMinimumSize(300, 300);
	widget->setMaximumWidth(400);

	widget = new QDockWidget("3D Inspector", MainWindow.get());
	auto scene3DInspector = std::make_unique<Scene3DInspector>(nullptr);
	widget->setWidget(scene3DInspector.get());
	MainWindow->addDockWidget(Qt::RightDockWidgetArea, widget);
	widget->setMinimumSize(300, 300);

	installEventFilter(this);


	ProjectManager = new ::ProjectManager();

	auto inspectorMgr = std::make_unique<::InspectorManager>();

	auto sceneMgr = std::make_unique<SceneManager>();
	inspectorMgr->SetSceneManager(sceneMgr.get());
	ProjectManager->SetSceneManager(std::move(sceneMgr));

	auto commandsMgr = std::make_unique<::CommandsManager>();
	inspectorMgr->SetCommandsManager(commandsMgr.get());
	CommandsManager = commandsMgr.get();
	ProjectManager->SetCommandsManager(std::move(commandsMgr));

	inspectorMgr->SetPointDialog(std::move(std::make_unique<PointDialog>()));
	inspectorMgr->SetHeightMapDialog(std::move(std::make_unique<HeightMapDialog>()));
	inspectorMgr->SetSceneResolutionDialog(std::move(std::make_unique<SceneResolutionDialog>()));
	inspectorMgr->AddInspector(std::move(pointInspector));
	inspectorMgr->AddInspector(std::move(sceneInspector));
	inspectorMgr->AddInspector(std::move(heightMapInspector));
	inspectorMgr->AddInspector(std::move(scene3DInspector));
	InspectorManager = inspectorMgr.get();
	ProjectManager->SetInspectorManager(std::move(inspectorMgr));

	HelpDialog = std::make_unique<::HelpDialog>(this);
}

// ************************************************************************************************
void Application::ChangeResolution()
{
	InspectorManager->ChangeSceneResolution();
}

// ************************************************************************************************
bool Application::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::Type::KeyPress)
	{
		if (((QKeyEvent*)event)->isAutoRepeat())
			((QKeyEvent*)event)->ignore();
		else
		{
			switch (((QKeyEvent*)event)->key())
			{
			case Qt::Key::Key_Control:
				CtrlPressed = true;
				break;

			case Qt::Key::Key_Shift:
				ShiftPressed = true;
				break;

			case Qt::Key::Key_Z:
				ZPressed = true;
				break;
			}
		}
		if (CtrlPressed && ShiftPressed && ZPressed && !DuringEvent)
		{
			DuringEvent = true;
			gApp->Redo();
		}
		else if (CtrlPressed && ZPressed && !DuringEvent)
		{
			DuringEvent = true;
			gApp->Undo();
		}
	}
	else if (event->type() == QEvent::Type::KeyRelease)
	{
		if (((QKeyEvent*)event)->isAutoRepeat())
			((QKeyEvent*)event)->ignore();
		else
		{
			switch (((QKeyEvent*)event)->key())
			{
			case Qt::Key::Key_Control:
				CtrlPressed = false;
				DuringEvent = false;
				break;

			case Qt::Key::Key_Shift:
				ShiftPressed = false;
				DuringEvent = false;
				break;

			case Qt::Key::Key_Z:
				ZPressed = false;
				DuringEvent = false;
				break;
			}
		}
	}

	return false;
}

// ************************************************************************************************
void Application::Undo()
{
	CommandsManager->Undo();
}

// ************************************************************************************************
void Application::Redo()
{
	CommandsManager->Redo();
}

// ************************************************************************************************
void Application::Help()
{
	HelpDialog->Show();
}
