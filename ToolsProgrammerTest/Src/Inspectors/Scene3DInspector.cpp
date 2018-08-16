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

#include <Qt3DCore/qaspectengine.h>
#include <Qt3DRender/qobjectpicker.h>

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

#include <QtCore/QDebug>

#include <QtWidgets/qgridlayout.h>



#include "Managers/IInspectorManager.hpp"

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
	cameraEntity->setFieldOfView(85);
	cameraEntity->setPosition(QVector3D(50, 50, 50));
	cameraEntity->setUpVector(QVector3D(0, 1, 0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));

	Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(Root);
	Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
	light->setColor("white");
	light->setIntensity(1);
	lightEntity->addComponent(light);
	Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
	lightTransform->setTranslation(cameraEntity->position());
	lightTransform->setRotationZ(45);
	lightEntity->addComponent(lightTransform);

	// For camera controls
	Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(Root);
	camController->setCamera(cameraEntity);

	// Set root object of the scene
	view->setRootEntity(Root);



	// mesh
	auto mesh = new Qt3DExtras::QCuboidMesh();
	// material
	auto material = new Qt3DExtras::QPhongMaterial();
	material->setDiffuse(QColor(QRgb(0xff0000)));
	// transform
	auto transform = new Qt3DCore::QTransform();
	transform->setTranslation(QVector3D(25, -1, -1));
	transform->setScale3D(QVector3D(50, 0.5f, 0.5f));
	// Cuboid
	auto axis = new Qt3DCore::QEntity(Root);
	axis->addComponent(mesh);
	axis->addComponent(material);
	axis->addComponent(transform);

	// mesh
	mesh = new Qt3DExtras::QCuboidMesh();
	// material
	material = new Qt3DExtras::QPhongMaterial();
	material->setDiffuse(QColor(QRgb(0x00ff00)));
	// transform
	transform = new Qt3DCore::QTransform();
	transform->setTranslation(QVector3D(-1, 25, -1));
	transform->setScale3D(QVector3D(0.5f, 50, 0.5f));
	// Cuboid
	axis = new Qt3DCore::QEntity(Root);
	axis->addComponent(mesh);
	axis->addComponent(material);
	axis->addComponent(transform);

	// mesh
	mesh = new Qt3DExtras::QCuboidMesh();
	// material
	material = new Qt3DExtras::QPhongMaterial();
	material->setDiffuse(QColor(QRgb(0x0000ff)));
	// transform
	transform = new Qt3DCore::QTransform();
	transform->setTranslation(QVector3D(-1, -1, 25));
	transform->setScale3D(QVector3D(0.5f, 0.5f, 50));
	// Cuboid
	axis = new Qt3DCore::QEntity(Root);
	axis->addComponent(mesh);
	axis->addComponent(material);
	axis->addComponent(transform);



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
}



//		public slots
// ************************************************************************************************
void Scene3DInspector::PointSpawned(const Point* point)
{
	// mesh
	auto cubeMesh = new Qt3DExtras::QCuboidMesh();

	// material
	auto cubeMaterial = new Qt3DExtras::QPhongMaterial();
	auto denominator = (float)point->PosY / Manager->GetSceneResolution().Y;
	auto r = int(0xff * denominator) * 0x010000;
	auto g = int(0xff * (1 - denominator)) * 0x000100;
	auto b = 0x000000;
	cubeMaterial->setDiffuse(QColor(QRgb(r + g + b)));

	// transform
	auto transform = new Qt3DCore::QTransform();
	transform->setTranslation(QVector3D(point->PosX, point->PosY, point->PosZ));

	// object picker
	auto picker = new Qt3DRender::QObjectPicker();
	auto helper = std::make_unique<PickHelper>(this, point->Id);
	connect(picker, &Qt3DRender::QObjectPicker::clicked, helper.get(), &Scene3DInspector::PickHelper::PickEvent);

	// entity
	auto entity = new Qt3DCore::QEntity(Root);
	entity->addComponent(cubeMesh);
	entity->addComponent(cubeMaterial);
	entity->addComponent(transform);
	entity->addComponent(picker);

	Points.insert(std::pair<size_t, Qt3DCore::QEntity*>(point->Id, entity));
	Materials.insert(std::pair<size_t, Qt3DExtras::QPhongMaterial*>(point->Id, cubeMaterial));
	Transforms.insert(std::pair<size_t, Qt3DCore::QTransform*>(point->Id, transform));
	PickHelpers.insert(std::pair<size_t, std::unique_ptr<PickHelper>>(point->Id, std::move(helper)));
}

// ************************************************************************************************
void Scene3DInspector::PointDestroyed(const Point* point)
{
	delete Points[point->Id];
	Points.erase(point->Id);
	Materials.erase(point->Id);
	Transforms.erase(point->Id);
	PickHelpers.erase(point->Id);

	AnySelected = false;
}

// ************************************************************************************************
void Scene3DInspector::PointSelected(const Point* point)
{
	if (!point)
	{
		if (AnySelected)
			Materials[SelectedPioint]->setDiffuse(LastSelectedColor);

		AnySelected = false;
	}
	else
	{
		if (AnySelected)
			Materials[SelectedPioint]->setDiffuse(LastSelectedColor);

		AnySelected = true;
		SelectedPioint = point->Id;
		LastSelectedColor = Materials[point->Id]->diffuse();
		Materials[point->Id]->setDiffuse(QColor(QRgb(0x3333ff)));
	}
}

// ************************************************************************************************
void Scene3DInspector::PointModified(const Point* point)
{
	auto transform = Transforms[point->Id];
	auto translation = transform->translation();

	translation.setX(point->PosX);
	translation.setY(point->PosY);
	translation.setZ(point->PosZ);

	transform->setTranslation(translation);


	auto material = Materials[point->Id];
	auto denominator = (float)point->PosY / Manager->GetSceneResolution().Y;
	auto r = int(0xff * denominator) * 0x010000;
	auto g = int(0xff * (1 - denominator)) * 0x000100;
	auto b = 0x000000;

	if (AnySelected && SelectedPioint == point->Id)
		LastSelectedColor = QColor(QRgb(r + g + b));
	else
		material->setDiffuse(QColor(QRgb(r + g + b)));
}

// ************************************************************************************************
void Scene3DInspector::PickHelper::PickEvent(Qt3DRender::QPickEvent* pick)
{
	Owner->Manager->SelectPoint(PointId);
}