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
}



//		public slots
// ************************************************************************************************
void HeightMapInspector::HeightMapLoaded(const QPixmap* heightMap)
{
	Image->setPixmap(*heightMap);
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
