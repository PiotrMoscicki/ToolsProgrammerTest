#include "HeightMapInspector.hpp"

#include <QtWidgets/qgridlayout.h>

using namespace TPT;

// ************************************************************************************************
HeightMapInspector::HeightMapInspector(QWidget* parent)
	: QWidget(parent)
{
	// layout
	setLayout(new QGridLayout(this));

	// content
	Image = new QLabel(this);
	layout()->addWidget(Image);
	
	// context menu
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &HeightMapInspector::customContextMenuRequested, this, &HeightMapInspector::SpawnContextMenu);

	ContextMenu = new QMenu(this);

		LoadHeightMapAction = new QAction("Spawn Point", this);
		ContextMenu->addAction(LoadHeightMapAction);
		connect(LoadHeightMapAction, &QAction::triggered, this, &HeightMapInspector::LoadHeightMap);
}

// ************************************************************************************************
void HeightMapInspector::SetManager(IInspectorManager* manager)
{
	connect(Manager, &IInspectorManager::HeightMapLoadedSignal, this, &HeightMapInspector::HeightMapLoaded);

	connect(Manager, &IInspectorManager::Update, this, &HeightMapInspector::Update);
	connect(Manager, &IInspectorManager::Reload, this, &HeightMapInspector::Reload);
}



//		public slots
// ************************************************************************************************
void HeightMapInspector::HeightMapLoaded(const QPixmap* heightMap)
{
	Image->setPixmap(*heightMap);
}

// ************************************************************************************************
void HeightMapInspector::Update()
{
	Image->setPixmap(*Manager->GetHeightMap());
}

// ************************************************************************************************
void HeightMapInspector::Reload()
{
	Image->setPixmap(*Manager->GetHeightMap());
}



//		private slots
// ************************************************************************************************
void HeightMapInspector::SpawnContextMenu(QPoint pos)
{
	ContextMenu->popup(this->mapToGlobal(pos));
}

// ************************************************************************************************
void HeightMapInspector::LoadHeightMap()
{
	Manager->LoadHeightMap();
}
