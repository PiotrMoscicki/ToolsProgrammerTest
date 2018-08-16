#pragma once

#include <QtWidgets/qdialog.h>

#include "Managers/Dialogs/IPointDialog.hpp"

class QTabWidget;
class QLabel;
class QLineEdit;
class QPushButton;

namespace TPT
{
	class PointDialog : public IPointDialog, public QDialog
	{
	public:
		PointDialog();

		std::unique_ptr<SpawnPointsCommand> SpawnPoints(ISceneManager* scene) override;
		std::unique_ptr<DestroyPointCommand> DestroyPoint(ISceneManager* scene, size_t id) override;

		void Reset() override;
		bool Canceled() override { return CanceledFlag; }

	private:
		QTabWidget* TabWidget;
		QLabel* NameLabel;		QLineEdit* NameField;
		QLabel* PositionLabel;	QLineEdit* PositionFields[2];
		QLabel* MapResolutionLabel;	QLineEdit* MapResolutionFields[2];
		QLabel* PointsResolutionLabel;	QLineEdit* PointsResolutionFields[2];
		QPushButton* CancelButton;		QPushButton* OkButton;

		bool CanceledFlag = true;

	private slots:
		void Ok();
		void Cancel();
	};
}