#pragma once

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qdialog.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>

#include "Managers/Dialogs/ISceneResolutionDialog.hpp"

namespace TPT
{
	class SceneResolutionDialog : public ISceneResolutionDialog, public QDialog
	{
	public:
		SceneResolutionDialog();

		std::unique_ptr<IDialogCommand> SetSceneResolution(ISceneManager* scene) override;

		void Reset() override;
		bool Canceled() override { return CanceledFlag; }

	private:
		QLabel* ResolutionLabel;		QLineEdit* ResolutionFields[3];
		QPushButton* CancelButton;		QPushButton* OkButton;

		bool CanceledFlag = true;

		SceneResolution CurrentResolution;

	private slots:
		void Ok();
		void Cancel();

		void XChanged();
		void ZChanged();
	};
}