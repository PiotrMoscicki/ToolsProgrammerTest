#pragma once

#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qmenu.h>

#include "Windows/Window.hpp"

namespace TPT
{
	class MainWindow : public Window
	{
		Q_OBJECT

	public:
		MainWindow();

	private:
		// main window menu actions
		std::unique_ptr<QMenuBar> MenuBar;
			std::unique_ptr<QMenu> FileMenu;
				std::unique_ptr<QAction> QuitAction;
				std::unique_ptr<QAction> LoadHeightMapAction;
			std::unique_ptr<QMenu> EditMenu;
				std::unique_ptr<QAction> UndoAction;
				std::unique_ptr<QAction> RedoAction;

	private slots:
		// file
		void Quit();
		void LoadHeightMap();

		// edit
		void Undo();
		void Redo();

	protected:
		void closeEvent(QCloseEvent* event) override;
	};
}