#include "PointInspector.hpp"

#include <QtWidgets/qgridlayout.h>

#include "Structures/Commands/PointModificationCommand.hpp"

using namespace TPT;

// ************************************************************************************************
PointInspector::PointInspector(QWidget* parent)
	: QWidget(parent)
{
	// layout
	auto gridLayout = new QGridLayout(this);

	gridLayout->setColumnStretch(0, 1);
	gridLayout->setColumnStretch(1, 1);
	gridLayout->setColumnStretch(2, 1);
	gridLayout->setColumnStretch(3, 1);

	for (size_t i = 0; i < 100; ++i)
		gridLayout->setRowStretch((int)i, 1);

	setLayout(gridLayout);

	//		content
	// name
	NameLabel = new QLabel(this);
	NameLabel->setText("Name");
	gridLayout->addWidget(NameLabel, 0, 0);

	NameField = new QLineEdit(this);
	NameField->setDisabled(true);
	gridLayout->addWidget(NameField, 0, 1, 1, 3);
	connect(NameField, &QLineEdit::editingFinished, this, &PointInspector::FieldModified);

	// id
	IdLabel = new QLabel(this);
	IdLabel->setText("Id");
	gridLayout->addWidget(IdLabel, 1, 0);

	IdField = new QLineEdit(this);
	IdField->setDisabled(true);
	gridLayout->addWidget(IdField, 1, 1, 1, 3);

	// position
	PositionLabel = new QLabel(this);
	PositionLabel->setText("Position");
	gridLayout->addWidget(PositionLabel, 2, 0);

	for (int i = 0; i < 3; ++i)
	{
		PositionFields[i] = new QLineEdit(this);
		PositionFields[i]->setDisabled(true);
		gridLayout->addWidget(PositionFields[i], 2, i + 1);
		connect(PositionFields[i], &QLineEdit::editingFinished, this, &PointInspector::FieldModified);
	}

}

// ************************************************************************************************
void PointInspector::SetManager(IInspectorManager* manager)
{
	Manager = manager;

	connect(Manager, &IInspectorManager::PointSelectedSignal, this, &PointInspector::PointSelected);
	connect(Manager, &IInspectorManager::PointModifiedSignal, this, &PointInspector::PointModified);

	connect(Manager, &IInspectorManager::HeightMapLoadedSignal, this, &PointInspector::HeightMapLoaded);
}



//		private slots
// ************************************************************************************************
void PointInspector::PointSelected(const Point* point)
{
	if (!point)
	{
		NameField->setText("");
		IdField->setText("");
		PositionFields[0]->setText("");
		PositionFields[1]->setText("");
		PositionFields[2]->setText("");

		NameField->setDisabled(true);

		PositionFields[0]->setDisabled(true);
		PositionFields[2]->setDisabled(true);
	}
	else
	{
		NameField->setDisabled(false);
		PositionFields[0]->setDisabled(false);
		PositionFields[2]->setDisabled(false);

		NameField->setText(point->Name);
		IdField->setText(QString::number(point->Id));
		PositionFields[0]->setText(QString::number(point->PosX));
		PositionFields[1]->setText(QString::number(point->PosY));
		PositionFields[2]->setText(QString::number(point->PosZ));
	}
}

// ************************************************************************************************
void PointInspector::PointModified(const Point* point)
{
	NameField->setText(point->Name);
	IdField->setText(QString::number(point->Id));
	PositionFields[0]->setText(QString::number(point->PosX));
	PositionFields[1]->setText(QString::number(point->PosY));
	PositionFields[2]->setText(QString::number(point->PosZ));
}

// ************************************************************************************************
void TPT::PointInspector::HeightMapLoaded(const QPixmap* heightMap)
{
	auto point = Manager->GetSelectedPoint();

	if (!point)
		return;

	NameField->setText(point->Name);
	IdField->setText(QString::number(point->Id));
	PositionFields[0]->setText(QString::number(point->PosX));
	PositionFields[1]->setText(QString::number(point->PosY));
	PositionFields[2]->setText(QString::number(point->PosZ));
}



//		private slots
// ************************************************************************************************
void PointInspector::FieldModified()
{
	auto undoValue = *Manager->GetSelectedPoint();
	auto redoValue = Point();

	redoValue.Name = NameField->text();
	redoValue.PosX = PositionFields[0]->text().toFloat();
	redoValue.PosY = PositionFields[1]->text().toFloat();
	redoValue.PosZ = PositionFields[2]->text().toFloat();

	auto cmd = std::make_unique<PointModificationCommand>(undoValue, redoValue, undoValue.Id, Manager);
	Manager->ModifyPoint(std::move(cmd));
}
