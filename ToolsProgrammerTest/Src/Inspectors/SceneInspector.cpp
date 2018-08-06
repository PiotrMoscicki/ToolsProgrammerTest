#include "SceneInspector.hpp"

#include <QtWidgets/qgridlayout.h>

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
	Tree->setHeaderLabels(QStringList() << "Name" << "ID");
	Tree->setAcceptDrops(false);
	Tree->setDragEnabled(false);
	connect(Tree, &QTreeWidget::itemSelectionChanged, this, &SceneInspector::SelectionChanged);
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

	connect(Manager, &IInspectorManager::Update, this, &SceneInspector::Update);
	connect(Manager, &IInspectorManager::Reload, this, &SceneInspector::Reload);
}



//		public slots
// ************************************************************************************************
void SceneInspector::PointSpawned(const Point* point)
{
	QTreeWidgetItem* entityTree = new QTreeWidgetItem(Tree);

	entityTree->setText(0, point->Name);
	entityTree->setText(1, QString::number(point->Id));
	ItemToPoint.insert(std::pair<QTreeWidgetItem*, const Point*>(entityTree, point));
	PointToItem.insert(std::pair<const Point*, QTreeWidgetItem*>(point, entityTree));
}

// ************************************************************************************************
void SceneInspector::PointDestroyed(const Point* point)
{
	delete PointToItem[point];

	ItemToPoint.erase(PointToItem[point]);
	PointToItem.erase(point);
}

// ************************************************************************************************
void SceneInspector::PointSelected(const Point* point)
{
	if (!point)
		return;

	PointToItem[point]->setSelected(true);
}

// ************************************************************************************************
void SceneInspector::PointModified(const Point* point)
{
	PointToItem[point]->setText(0, point->Name);
}

// ************************************************************************************************
void SceneInspector::Update()
{
	for (auto pair : ItemToPoint)
		pair.first->setText(0, pair.second->Name);
}

// ************************************************************************************************
void SceneInspector::Reload()
{
	Tree->reset();

	auto points = Manager->GetPoints();

	for (auto point : points)
	{
		QTreeWidgetItem* entityTree = new QTreeWidgetItem(Tree);

		entityTree->setText(0, point->Name);
		entityTree->setText(1, QString::number(point->Id));
		ItemToPoint.insert(std::pair<QTreeWidgetItem*, const Point*>(entityTree, point));
		PointToItem.insert(std::pair<const Point*, QTreeWidgetItem*>(point, entityTree));
	}
}



//		private slots
// ************************************************************************************************
void SceneInspector::SelectionChanged()
{
	if (Tree->selectedItems()[0] != nullptr)
		Manager->SelectPoint(ItemToPoint[Tree->selectedItems()[0]]->Id);
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
