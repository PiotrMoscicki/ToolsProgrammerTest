#include "Pch.hpp"


#include "SceneInspector.hpp"

#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qtreewidget.h>

#include "Managers/IInspectorManager.hpp"
#include "Structures/Commands/PointModificationCommand.hpp"

using namespace TPT;

// ************************************************************************************************
SceneInspector::SceneInspector(QWidget* parent)
	: QWidget(parent)
{
	//layout
	setLayout(new QGridLayout(this));

	// content
	Tree = new QTreeWidget(this);
	Tree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	Tree->setHeaderLabels(QStringList() << "Name" << "X" << "Z");
	Tree->setAcceptDrops(false);
	Tree->setDragEnabled(false);
	Tree->setEditTriggers(QAbstractItemView::DoubleClicked);
	connect(Tree, &QTreeWidget::itemSelectionChanged, this, &SceneInspector::SelectionChanged);
	connect(Tree, &QTreeWidget::itemChanged, this, &SceneInspector::FieldModified);
	layout()->addWidget(Tree);

	// context menu
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &SceneInspector::customContextMenuRequested, this, &SceneInspector::SpawnContextMenu);

	ContextMenu = new QMenu(this);

		SpawnPointAction = new QAction("Spawn Point", this);
		ContextMenu->addAction(SpawnPointAction);
		connect(SpawnPointAction, &QAction::triggered, this, &SceneInspector::SpawnPoint);

		DestroyPointAction = new QAction("Destroy Point", this);
		ContextMenu->addAction(DestroyPointAction);
		connect(DestroyPointAction, &QAction::triggered, this, &SceneInspector::DestroyPoint);

}

// ************************************************************************************************
void SceneInspector::SetManager(IInspectorManager* manager)
{
	Manager = manager;

	connect(Manager, &IInspectorManager::PointSpawnedSignal, this, &SceneInspector::PointSpawned);
	connect(Manager, &IInspectorManager::PointDestroyedSignal, this, &SceneInspector::PointDestroyed);
	connect(Manager, &IInspectorManager::PointSelectedSignal, this, &SceneInspector::PointSelected);
	connect(Manager, &IInspectorManager::PointModifiedSignal, this, &SceneInspector::PointModified);
}



//		public slots
// ************************************************************************************************
void SceneInspector::PointSpawned(const Point* point)
{
	SilenceItemChanged = true;

	QTreeWidgetItem* item = new QTreeWidgetItem(Tree);

	item->setFlags(item->flags() | Qt::ItemIsEditable);
	item->setText(0, point->Name);
	item->setText(1, QString::number(point->PosX));
	item->setText(2, QString::number(point->PosZ));

	ItemToPoint.insert(std::pair<QTreeWidgetItem*, const Point*>(item, point));
	PointToItem.insert(std::pair<const Point*, QTreeWidgetItem*>(point, item));

	SilenceItemChanged = false;
}

// ************************************************************************************************
void SceneInspector::PointDestroyed(const Point* point)
{
	SilenceSelectionChanged = true;

	delete PointToItem[point];

	ItemToPoint.erase(PointToItem[point]);
	PointToItem.erase(point);

	Tree->clearSelection();

	SilenceSelectionChanged = false;
}

// ************************************************************************************************
void SceneInspector::PointSelected(const Point* point)
{
	SilenceSelectionChanged = true;

	if (!point)
		return;

	Tree->clearSelection();
	PointToItem[point]->setSelected(true);

	SilenceSelectionChanged = false;
}

// ************************************************************************************************
void SceneInspector::PointModified(const Point* point)
{
	SilenceItemChanged = true;

	auto item = PointToItem[point];

	item->setText(0, point->Name);
	item->setText(1, QString::number(point->PosX));
	item->setText(2, QString::number(point->PosZ));

	SilenceItemChanged = false;
}



//		private slots
// ************************************************************************************************
void SceneInspector::SelectionChanged()
{
	if (SilenceSelectionChanged)
		return;

	if (Tree->selectedItems().count() > 0)
		Manager->SelectPoint(ItemToPoint[Tree->selectedItems()[0]]->Id);
	else
		Manager->DeselectPoint();
}

// ************************************************************************************************
void SceneInspector::FieldModified()
{
	if (SilenceItemChanged)
		return;

	auto item = PointToItem[Manager->GetSelectedPoint()];

	auto undoValue = *Manager->GetSelectedPoint();
	auto redoValue = Point();

	redoValue.Name = item->text(0);
	redoValue.PosX = item->text(1).toInt();
	redoValue.PosY = undoValue.PosY;
	redoValue.PosZ = item->text(2).toInt();

	auto cmd = std::make_unique<PointModificationCommand>(undoValue, redoValue, undoValue.Id, Manager);
	Manager->ModifyPoint(std::move(cmd));
}

// ************************************************************************************************
void SceneInspector::SpawnContextMenu(QPoint pos)
{
	ContextMenu->popup(this->mapToGlobal(pos));
}

// ************************************************************************************************
void SceneInspector::SpawnPoint()
{
	Manager->SpawnPoint();
}

// ************************************************************************************************
void SceneInspector::DestroyPoint()
{
	Manager->DestroyPoint();
}
