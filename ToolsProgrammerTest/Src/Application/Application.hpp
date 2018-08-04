#pragma once

#include <QtWidgets/qapplication.h>
#include <QtCore/qtimer.h>
#include <QtWidgets/qmainwindow.h>

namespace TPT
{
	class Application : public QApplication
	{
		Q_OBJECT

	public:
		Application(int argc, char *argv[]);

	private:
		std::unique_ptr<QMainWindow> MainWindow;
	};

	extern Application* gApp;
}
