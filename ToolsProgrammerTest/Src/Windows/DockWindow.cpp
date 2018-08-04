#include "DockWindow.hpp"

#include "QtWidgets/QStylePainter"

#include "Windows/Window.hpp"
#include "Windows/Widget.hpp"

using namespace TPT;

DockWindow::DockWindow(const QString& title, Widget* widget)
	: QDockWidget(title), Title(title)
{
	widget->setParent(this);

	setWidget(widget);

	connect(this, &QDockWidget::topLevelChanged, this, 
		[object = this](bool topLevel) { if (topLevel) gApp->DockMgr->WidgetCatchEvent(object); });
}

void DockWindow::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);

	painter.setPen(QColor(225, 159, 4));
	painter.drawLine(10, 20, width() - 10, 20);
	painter.setPen(Qt::lightGray);
	painter.setFont(QFont("Consolas", 9, QFont::Bold));
	painter.drawText(QRect(10, 0, width(), 20), Title);

	QWidget::paintEvent(e);
}