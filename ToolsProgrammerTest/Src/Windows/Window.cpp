#include "Window.hpp"

#include <QtWidgets/qdockwidget.h>
#include <QtCore/qtimer.h>

#include "Windows/DockWindow.hpp"

using namespace TPT;

Window::Window()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
}

void Window::AddDockWindow(Qt::DockWidgetArea area, DockWindow* wnd, bool isInitialization)
{
	if(Window* window = dynamic_cast<Window*>(wnd->parent()))
		window->RemoveDockWindow(wnd);
	
	if(isInitialization)
		addDockWidget(area, wnd);
	else
		QTimer::singleShot(1, this, [a = area, w = wnd, object = this]() 
			{ object->addDockWidget(a, w); w->show(); });

	DockWindows.push_back(wnd);
}

void Window::RemoveDockWindow(DockWindow* wnd)
{
	DockWindows.erase(std::remove(DockWindows.begin(), DockWindows.end(), wnd), DockWindows.end());
	removeDockWidget(wnd);
}

void Window::closeEvent(QCloseEvent* event)
{
	auto windows = DockWindows;

	for (auto wnd : windows)
		gApp->Ui.MainWindow->AddDockWindow(Qt::DockWidgetArea::LeftDockWidgetArea, wnd);

	gApp->Ui.Windows.Remove(this);
}
