#pragma once

#include <QtWidgets/qtreewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qdialog.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtabwidget.h>

#include "Managers/Dialogs/IPointDialog.hpp"

namespace TPT
{
	class PointDialog : public IPointDialog, public QDialog
	{
	public:
		PointDialog();

		std::vector<Point*> SpawnPoints(ISceneManager* scene) override;
		void DestroyPoint(ISceneManager* scene, size_t id) override;

		void Reset() override;
		bool Canceled() override;

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