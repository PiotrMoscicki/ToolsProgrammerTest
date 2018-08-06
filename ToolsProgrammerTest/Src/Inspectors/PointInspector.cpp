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
	setLayout(gridLayout);

	//		content
	// name
	NameLabel = new QLabel(this);
	gridLayout->addWidget(NameLabel, 0, 0);

	NameField = new QLineEdit(this);
	gridLayout->addWidget(NameField, 0, 1, 1, 3);
	connect(NameField, &QLineEdit::editingFinished, this, &PointInspector::FieldModified);

	// position
	PositionLabel = new QLabel(this);
	gridLayout->addWidget(PositionLabel, 1, 0);

	for (int i = 0; i < 3; ++i)
	{
		PositionFields[i] = new QLineEdit(this);
		gridLayout->addWidget(PositionFields[i], 1, i + 1);
		connect(PositionFields[i], &QLineEdit::editingFinished, this, &PointInspector::FieldModified);
	}

}

// ************************************************************************************************
void PointInspector::SetManager(IInspectorManager* manager)
{
	Manager = manager;

	connect(Manager, &IInspectorManager::PointSelectedSignal, this, &PointInspector::PointSelected);
	connect(Manager, &IInspectorManager::PointModifiedSignal, this, &PointInspector::PointModified);

	connect(Manager, &IInspectorManager::Update, this, &PointInspector::Update);
	connect(Manager, &IInspectorManager::Reload, this, &PointInspector::Reload);
}



//		private slots
// ************************************************************************************************
void PointInspector::PointSelected(const Point* point)
{
	if (!point)
		return;

	NameField->setText(point->Name);
	PositionFields[0]->setText(QString::number(point->Position.x()));
	PositionFields[1]->setText(QString::number(point->Position.y()));
	PositionFields[2]->setText(QString::number(point->Position.z()));
}

// ************************************************************************************************
void PointInspector::PointModified(const Point* point)
{
	NameField->setText(point->Name);
	PositionFields[0]->setText(QString::number(point->Position.x()));
	PositionFields[1]->setText(QString::number(point->Position.y()));
	PositionFields[2]->setText(QString::number(point->Position.z()));
}

// ************************************************************************************************
void PointInspector::Update()
{
	auto point = Manager->GetSelectedPoint();

	NameField->setText(point->Name);
	PositionFields[0]->setText(QString::number(point->Position.x()));
	PositionFields[1]->setText(QString::number(point->Position.y()));
	PositionFields[2]->setText(QString::number(point->Position.z()));
}

// ************************************************************************************************
void PointInspector::Reload()
{
	auto point = Manager->GetSelectedPoint();

	NameField->setText(point->Name);
	PositionFields[0]->setText(QString::number(point->Position.x()));
	PositionFields[1]->setText(QString::number(point->Position.y()));
	PositionFields[2]->setText(QString::number(point->Position.z()));
}



//		private slots
// ************************************************************************************************
void PointInspector::FieldModified()
{
	auto undoValue = *Manager->GetSelectedPoint();
	auto redoValue = Point();

	redoValue.Name = NameField->text();
	redoValue.Position.setX(PositionFields[0]->text().toFloat());
	redoValue.Position.setY(PositionFields[1]->text().toFloat());
	redoValue.Position.setZ(PositionFields[2]->text().toFloat());

	auto cmd = std::make_unique<PointModificationCommand>(undoValue, redoValue, undoValue.Id, Manager);
}
