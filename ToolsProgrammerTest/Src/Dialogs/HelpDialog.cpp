#include "Pch.hpp"

#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>

using namespace TPT;

// ************************************************************************************************
HelpDialog::HelpDialog(QObject * parent)
{
	auto gridLayout = new QGridLayout(this);
	gridLayout->setColumnStretch(0, 3);
	gridLayout->setColumnStretch(1, 1);

	TextLabel = new QLabel(this);
	TextLabel->setText("Camera move - arrows + PgUp + PgDn\nCamera look - mouse\nUndo/Redo - Ctrl+Z / Ctrl+Shift+Z\nUse context menus.");
	gridLayout->addWidget(TextLabel, 0, 0, 1, 2);

	OkButton = new QPushButton(this);
	OkButton->setText("Ok");
	connect(OkButton, &QPushButton::clicked, this, &HelpDialog::Ok);
	gridLayout->addWidget(OkButton, 1, 1);
}

// ************************************************************************************************
void HelpDialog::Show()
{
	exec();
}



//		private slots
// ************************************************************************************************
void HelpDialog::Ok()
{
	close();
}
