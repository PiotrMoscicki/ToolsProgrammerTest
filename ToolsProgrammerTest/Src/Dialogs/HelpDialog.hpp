#pragma once

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qdialog.h>
#include <QtWidgets/qlabel.h>

#include "Dialogs/IDialog.hpp"

namespace TPT
{
	class HelpDialog : public IDialog, public QDialog
	{
	public:
		HelpDialog(QObject* parent);

		void Show();

		void Reset() override {}
		bool Canceled() override { return CanceledFlag; }

	private:
		QLabel* TextLabel;
		QPushButton* OkButton;

		bool CanceledFlag = false;

	private slots:
		void Ok();
	};
}