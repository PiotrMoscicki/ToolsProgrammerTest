#include "Scene3DInspector.hpp"

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>
#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <QtCore/QDebug>

#include <QtWidgets/qgridlayout.h>

using namespace TPT;

// ************************************************************************************************
Scene3DInspector::Scene3DInspector(QWidget* parent)
	: QWidget(parent)
{
	setLayout(new QGridLayout(this));

	// view
	Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
	view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
	QWidget *container = QWidget::createWindowContainer(view);

	// input
	Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
	view->registerAspect(input);

	// root
	Root = new Qt3DCore::QEntity();

	// Camera
	Qt3DRender::QCamera *cameraEntity = view->camera();

	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
	cameraEntity->setUpVector(QVector3D(0, 1, 0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));

	Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(Root);
	Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
	light->setColor("white");
	light->setIntensity(1);
	lightEntity->addComponent(light);
	Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
	lightTransform->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform);

	// For camera controls
	Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(Root);
	camController->setCamera(cameraEntity);

	// mesh
	CubeMesh = new Qt3DExtras::QCuboidMesh();

	// material
	CubeMaterial = new Qt3DExtras::QPhongMaterial();
	CubeMaterial->setDiffuse(QColor(QRgb(0x665423)));

	// Set root object of the scene
	view->setRootEntity(Root);

	layout()->addWidget(container);
}

// ************************************************************************************************
void Scene3DInspector::SetManager(IInspectorManager* manager)
{
	Manager = manager;

	connect(Manager, &IInspectorManager::PointSpawnedSignal, this, &Scene3DInspector::PointSpawned);
	connect(Manager, &IInspectorManager::PointDestroyedSignal, this, &Scene3DInspector::PointDestroyed);
	connect(Manager, &IInspectorManager::PointSelectedSignal, this, &Scene3DInspector::PointSelected);
	connect(Manager, &IInspectorManager::PointModifiedSignal, this, &Scene3DInspector::PointModified);

	connect(Manager, &IInspectorManager::HeightMapLoadedSignal, this, &Scene3DInspector::HeightMapLoaded);
}



//		public slots
// ************************************************************************************************
void TPT::Scene3DInspector::PointSpawned(const Point* point)
{
	// transform
	auto transform = new Qt3DCore::QTransform();
	transform->setTranslation(QVector3D(point->PosX, point->PosY, point->PosZ));

	// Cuboid
	auto entity = new Qt3DCore::QEntity(Root);
	entity->addComponent(CubeMesh);
	entity->addComponent(CubeMaterial);
	entity->addComponent(transform);
}

// ************************************************************************************************
void TPT::Scene3DInspector::PointDestroyed(const Point* point)
{
}

// ************************************************************************************************
void Scene3DInspector::PointSelected(const Point* point)
{
}

// ************************************************************************************************
void TPT::Scene3DInspector::PointModified(const Point* point)
{
}

// ************************************************************************************************
void TPT::Scene3DInspector::HeightMapLoaded(const QPixmap* heightMap)
{
}
