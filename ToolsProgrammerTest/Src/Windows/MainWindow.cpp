#include "MainWindow.hpp"

#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qstylefactory>
#include <qcloseevent>

using namespace TPT;

MainWindow::MainWindow()
	: Window()
{
	setWindowTitle("ToolsProgrammertest Editor");
	resize(1280, 720);;

	// menu bar
	MenuBar = std::make_unique<QMenuBar>();
	setMenuBar(MenuBar.get());


		// file menu
		FileMenu = std::make_unique<QMenu>();
		MenuBar->addAction(FileMenu->menuAction());
		FileMenu->setTitle("File");

			QuitAction = std::make_unique<QAction>();
			FileMenu->addAction(QuitAction.get());
			QuitAction->setText("Quit");
			connect(QuitAction.get(), &QAction::triggered, this, &MainWindow::Quit);
}

void MainWindow::Quit()
{
	close();
}

void MainWindow::Undo()
{
}

void MainWindow::Redo()
{
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (gApp->ProjectMgr->IsOpened())
	{
		QMessageBox::StandardButton resBtn = QMessageBox::question(this, "PolyEditor",
			tr("Do you want to save your changes before closing?\n"),
			QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
			QMessageBox::Yes);

		if (resBtn == QMessageBox::Yes)
		{
			gApp->ProjectMgr->Save();
			gApp->ProjectMgr->Close();
			event->accept();
		}
		else if (resBtn == QMessageBox::No)
		{
			gApp->ProjectMgr->Close();
			event->accept();
		}
		else
			event->ignore();

	}
	else
	{
		QMessageBox::StandardButton resBtn = QMessageBox::question(this, "PolyEditor",
			tr("Do you really want to exit?\n"),
			QMessageBox::No | QMessageBox::Yes,
			QMessageBox::Yes);

		if (resBtn != QMessageBox::Yes)
			event->ignore();
		else 
			event->accept();
	}
}
