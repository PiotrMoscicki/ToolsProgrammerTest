#include "HeightMapInspector.hpp"

#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qlabel.h>
#include <QtGui/qpixmap.h>

#include "Managers/IInspectorManager.hpp"

using namespace TPT;

// ************************************************************************************************
HeightMapInspector::HeightMapInspector(QWidget* parent)
	: QWidget(parent)
{
	// layout
	setLayout(new QGridLayout(this));
	setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));

	// content
	Image = new QLabel(this);
	layout()->addWidget(Image);
	
	// context menu
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &HeightMapInspector::customContextMenuRequested, this, &HeightMapInspector::SpawnContextMenu);

	ContextMenu = new QMenu(this);

		LoadHeightMapAction = new QAction("Load Height Map", this);
		ContextMenu->addAction(LoadHeightMapAction);
		connect(LoadHeightMapAction, &QAction::triggered, this, &HeightMapInspector::LoadHeightMap);
}

// ************************************************************************************************
void HeightMapInspector::SetManager(IInspectorManager* manager)
{
	Manager = manager;

	connect(Manager, &IInspectorManager::HeightMapLoadedSignal, this, &HeightMapInspector::HeightMapLoaded);
}



//		public slots
// ************************************************************************************************
void HeightMapInspector::HeightMapLoaded(const QPixmap* heightMap)
{
	HeightMap = heightMap;
	if (!heightMap)
		return;

	Image->setPixmap(heightMap->scaled(Image->width(), Image->height(), Qt::KeepAspectRatio));
}



//		private slots
// ************************************************************************************************
void HeightMapInspector::SpawnContextMenu(QPoint pos)
{
	ContextMenu->popup(this->mapToGlobal(pos));
}

// ************************************************************************************************
void HeightMapInspector::resizeEvent(QResizeEvent* e)
{
	if (HeightMap)
		Image->setPixmap(HeightMap->scaled(Image->width(), Image->height(), Qt::KeepAspectRatio));

	QWidget::resizeEvent(e);
}

// ************************************************************************************************
void HeightMapInspector::LoadHeightMap()
{
	Manager->LoadHeightMap();
}
