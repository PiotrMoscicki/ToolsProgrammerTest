#include "Application.hpp"

#include <QtWidgets/QStyleFactory>
#include <QtWidgets/qdockwidget.h>

using namespace TPT;

namespace TPT
{
	Application* gApp = nullptr;
}

Application::Application(int argc, char *argv[])
	: QApplication(argc, argv), MainWindow(std::move(std::make_unique<QMainWindow>()))
{
	gApp = this;

	setStyle(QStyleFactory::create("Fusion"));

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(45, 45, 45));
	darkPalette.setColor(QPalette::WindowText, Qt::lightGray);
	darkPalette.setColor(QPalette::Base, QColor(30, 30, 30));
	darkPalette.setColor(QPalette::AlternateBase, QColor(255, 0, 0)); // no idea what's this
	darkPalette.setColor(QPalette::ToolTipBase, QColor(40, 40, 40));
	darkPalette.setColor(QPalette::ToolTipText, Qt::lightGray);
	darkPalette.setColor(QPalette::Text, Qt::lightGray);
	darkPalette.setColor(QPalette::Button, QColor(55, 55, 55));
	darkPalette.setColor(QPalette::ButtonText, Qt::lightGray);
	darkPalette.setColor(QPalette::BrightText, QColor(255, 0, 0)); // no idea what's this

	darkPalette.setColor(QPalette::Highlight, QColor(225, 159, 4));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::LinkVisited, QColor(150, 0, 150));

	qApp->setPalette(darkPalette);

	qApp->setStyleSheet("QToolTip { color: #000000; background-color: #e19f04; border: 1px solid black; } \
						 QDockWidget { font-family: \"Bennet\" } \
						 QWidget { font-family: \"Consolas\" } \
						 QComboBox:disabled { color: #c0c0c0; background-color: #242424; } \
						 QComboBox { color: #c0c0c0; background-color: #323232; } \
						 QLineEdit:disabled { color: #c0c0c0; background-color: #323232; } \
						 QLineEdit { color: #c0c0c0; background-color: #404040; }");

	MainWindow->setWindowTitle("ToolsProgrammerTest Editor");
	MainWindow->resize(1280, 720);
	MainWindow->show();

	auto widget = new QDockWidget("3D Inspector", MainWindow.get());
	MainWindow->addDockWidget(Qt::TopDockWidgetArea, widget);

	widget = new QDockWidget("Texture Inspector", MainWindow.get());
	MainWindow->addDockWidget(Qt::TopDockWidgetArea, widget);
	
	widget = new QDockWidget("Point Inspector", MainWindow.get());
	MainWindow->addDockWidget(Qt::TopDockWidgetArea, widget);
	
	widget = new QDockWidget("Scene Inspector", MainWindow.get());
	MainWindow->addDockWidget(Qt::TopDockWidgetArea, widget);

}