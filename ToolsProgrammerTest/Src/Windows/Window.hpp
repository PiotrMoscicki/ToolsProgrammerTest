#pragma once

#include <QtWidgets/qmainwindow.h>

#include <vector>

namespace TPT
{
	class DockWindow;

	class Window : public QMainWindow
	{
	public:
		Window();

		size_t DockWindowsCount() { return DockWindows.size; }

		void AddDockWindow(Qt::DockWidgetArea area, DockWindow* wnd, bool isInitialization = false);
		void RemoveDockWindow(DockWindow* widget);

	private:
		std::vector<DockWindow*> DockWindows;

		void closeEvent(QCloseEvent* event) override;
	};
}