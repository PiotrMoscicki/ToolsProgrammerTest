#include "Pch.hpp"

#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtabwidget.h>

using namespace TPT;

// ************************************************************************************************
PointDialog::PointDialog()
{
	auto gridLayout = new QGridLayout(this);

	TabWidget = new QTabWidget(this);
	gridLayout->addWidget(TabWidget, 0, 0, 1, 3);

	//		single point 
	auto singlePointWidget = new QWidget(TabWidget);
	auto singlePointLayout = new QGridLayout(singlePointWidget);
	singlePointLayout->setColumnStretch(0, 1);
	singlePointLayout->setColumnStretch(1, 1);
	singlePointLayout->setColumnStretch(2, 1);

	NameLabel = new QLabel(singlePointWidget);
	NameLabel->setText("Name");
	singlePointLayout->addWidget(NameLabel, 0, 0);

	NameField = new QLineEdit(singlePointWidget);
	singlePointLayout->addWidget(NameField, 0, 1, 1, 2);

	PositionLabel = new QLabel(singlePointWidget);
	PositionLabel->setText("Position");
	singlePointLayout->addWidget(PositionLabel, 1, 0);

	PositionFields[0] = new QLineEdit(singlePointWidget);
	singlePointLayout->addWidget(PositionFields[0], 1, 1);

	PositionFields[1] = new QLineEdit(singlePointWidget);
	singlePointLayout->addWidget(PositionFields[1], 1, 2);

	TabWidget->addTab(singlePointWidget, tr("Single Point"));

	//		multiple points 
	auto multiplePointWidget = new QWidget(TabWidget);
	auto multiplePointLayout = new QGridLayout(multiplePointWidget);
	multiplePointLayout->setColumnStretch(0, 1);
	multiplePointLayout->setColumnStretch(1, 1);
	multiplePointLayout->setColumnStretch(2, 1);

	MapResolutionLabel = new QLabel(multiplePointWidget);
	MapResolutionLabel->setText("Map Resolution");
	multiplePointLayout->addWidget(MapResolutionLabel, 0, 0);

	MapResolutionFields[0] = new QLineEdit(multiplePointWidget);
	MapResolutionFields[0]->setDisabled(true);
	multiplePointLayout->addWidget(MapResolutionFields[0], 0, 1);

	MapResolutionFields[1] = new QLineEdit(multiplePointWidget);
	MapResolutionFields[1]->setDisabled(true);
	multiplePointLayout->addWidget(MapResolutionFields[1], 0, 2);

	PointsResolutionLabel = new QLabel(multiplePointWidget);
	PointsResolutionLabel->setText("Points Resolution");
	multiplePointLayout->addWidget(PointsResolutionLabel, 1, 0);

	PointsResolutionFields[0] = new QLineEdit(multiplePointWidget);
	multiplePointLayout->addWidget(PointsResolutionFields[0], 1, 1);

	PointsResolutionFields[1] = new QLineEdit(multiplePointWidget);
	multiplePointLayout->addWidget(PointsResolutionFields[1], 1, 2);

	TabWidget->addTab(multiplePointWidget, tr("Multiple Points"));


	OkButton = new QPushButton(this);
	OkButton->setText("Spawn");
	connect(OkButton, &QPushButton::clicked, this, &PointDialog::Ok);
	gridLayout->addWidget(OkButton, 1, 2);

	CancelButton = new QPushButton(this);
	CancelButton->setText("Cancel");
	connect(CancelButton, &QPushButton::clicked, this, &PointDialog::Cancel);
	gridLayout->addWidget(CancelButton, 1, 0);
}

// ************************************************************************************************
std::unique_ptr<SpawnPointsCommand> PointDialog::SpawnPoints(ISceneManager* scene)
{
	Reset();

	MapResolutionFields[0]->setText(QString::number(scene->GetSceneResolution().X));
	MapResolutionFields[1]->setText(QString::number(scene->GetSceneResolution().Z));

	exec();

	if (CanceledFlag)
		return nullptr;

	std::unique_ptr<SpawnPointsCommand> result;

	switch (TabWidget->currentIndex())
	{
	case 0:
	{
		result = std::make_unique<SpawnPointsCommand>(NameField->text()
			, PositionFields[0]->text().toInt(), PositionFields[1]->text().toInt(), scene);
		break;
	}

	case 1:
	{
		size_t pointsResolutionX = PointsResolutionFields[0]->text().toInt();
		size_t pointsResolutionZ = PointsResolutionFields[1]->text().toInt();

		if (pointsResolutionX == 0 || pointsResolutionZ == 0)
		{
			CanceledFlag = true;
			break;
		}

		if (pointsResolutionX * pointsResolutionZ > 4096)
		{
			auto box = new QMessageBox();
			box->setText("Spawning (and destroying) large amount of points may take a while.");
			box->exec();
			delete box;
		}

		size_t mapResolutionX = MapResolutionFields[0]->text().toInt();
		size_t mapResolutionZ = MapResolutionFields[1]->text().toInt();

		result = std::make_unique<SpawnPointsCommand>(pointsResolutionX, pointsResolutionZ
			, mapResolutionX, mapResolutionZ, scene);
	}
		break;

	default:
		throw new std::exception();
	}

	return std::move(result);
}

// ************************************************************************************************
std::unique_ptr<DestroyPointCommand> PointDialog::DestroyPoint(ISceneManager* scene, size_t id)
{
	Reset();

	auto cmd = std::make_unique<DestroyPointCommand>(id, scene);

	CanceledFlag = false;

	return std::move(cmd);
}

// ************************************************************************************************
void PointDialog::Reset()
{
	CanceledFlag = true;

	NameField->setText("");
	PositionFields[0]->setText("");
	PositionFields[1]->setText("");
	PointsResolutionFields[0]->setText("");
	PointsResolutionFields[1]->setText("");
}

// ************************************************************************************************
void PointDialog::Ok()
{
	CanceledFlag = false;

	close();
}

// ************************************************************************************************
void PointDialog::Cancel()
{
	close();
}
