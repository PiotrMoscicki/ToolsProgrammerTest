#pragma once

#include <QDockWidget>

namespace TPT
{
	class Window;
	class Widget;

	class DockWindow : public QDockWidget
	{
	public:
		DockWindow(const QString& title, Widget* widget);

		Window* GetOwner() const { return static_cast<Window*>(parent()); }

	protected:
		void paintEvent(QPaintEvent *e) override;

	private:
		QString Title;
	};
}