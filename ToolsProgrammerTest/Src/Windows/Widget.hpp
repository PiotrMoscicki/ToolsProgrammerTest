#pragma once

#include "QtWidgets/qwidget.h"

namespace TPT
{
	class Widget : public QWidget
	{
	public:
		Widget(QWidget* parent = nullptr) : QWidget(parent) {}
	};
}