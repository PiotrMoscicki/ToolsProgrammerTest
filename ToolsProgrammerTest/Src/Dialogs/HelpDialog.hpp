#pragma once

#include <QtWidgets/qdialog.h>

#include "Dialogs/IDialog.hpp"

class QLabel;
class QPushButton;
class QObject;

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