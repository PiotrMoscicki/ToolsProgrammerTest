#include "PointDialog.hpp"

#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qgridlayout.h>

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
	multiplePointLayout->addWidget(MapResolutionFields[0], 0, 1);

	MapResolutionFields[1] = new QLineEdit(multiplePointWidget);
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
std::vector<Point*> PointDialog::SpawnPoints(ISceneManager* scene)
{
	Reset();

	exec();

	if (CanceledFlag)
		return {};

	auto result = std::vector<Point*>();

	switch (TabWidget->currentIndex())
	{
	case 0:
	{
		auto point = scene->SpawnPoint();
		point->Name = NameField->text();
		point->PosX = PositionFields[0]->text().toInt();
		point->PosZ = PositionFields[1]->text().toInt();
		result.push_back(point);
	}
		break;

	case 1:
	{
		size_t pointsResolutionX = PointsResolutionFields[0]->text().toInt();
		size_t pointsResolutionY = PointsResolutionFields[1]->text().toInt();

		if (pointsResolutionX == 0 || pointsResolutionY == 0)
			break;

		if (pointsResolutionX * pointsResolutionY > 4096)
		{
			auto box = new QMessageBox();
			box->setText("You don't want to do that...");
			box->exec();
			delete box;
			break;
		}

		size_t mapResolutionX = MapResolutionFields[0]->text().toInt();
		size_t mapResolutionY = MapResolutionFields[1]->text().toInt();

		float deltaX = (float)mapResolutionX / pointsResolutionX;
		float deltaY = (float)mapResolutionY / pointsResolutionY;

		for (float x = 0; x < mapResolutionX; x += deltaX)
			for (float y = 0; y < mapResolutionY; y += deltaY)
			{
				auto point = scene->SpawnPoint();
				point->PosX = x;
				point->PosZ = y;
				result.push_back(point);
			}
	}
		break;

	default:
		throw new std::exception();
	}

	return result;
}

// ************************************************************************************************
void PointDialog::DestroyPoint(ISceneManager* scene, size_t id)
{
	Reset();

	scene->DestroyPoint(id);

	CanceledFlag = false;
}

// ************************************************************************************************
void PointDialog::Reset()
{
	CanceledFlag = true;
	NameField->setText("");
	PositionFields[0]->setText("");
	PositionFields[1]->setText("");
}

// ************************************************************************************************
bool PointDialog::Canceled()
{
	return CanceledFlag;
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
