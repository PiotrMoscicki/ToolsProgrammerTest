#pragma once

#include <QtWidgets/qwidget.h>

#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DCore/qentity.h>

#include "Inspectors/IInspector.hpp"
#include "Managers/IInspectorManager.hpp"

namespace TPT
{
	class Scene3DInspector : public IInspector, public QWidget
	{
	public:
		Scene3DInspector(QWidget* parent);

		void SetManager(IInspectorManager* manager) override;

	public slots:
		void PointSpawned(const Point* point);
		void PointDestroyed(const Point* point);
		void PointSelected(const Point* point);
		void PointModified(const Point* point);

		void HeightMapLoaded(const QPixmap* heightMap);

	private:
		IInspectorManager* Manager = nullptr;

		Qt3DExtras::QCuboidMesh* CubeMesh;
		Qt3DExtras::QPhongMaterial* CubeMaterial;
		
		Qt3DCore::QEntity* Root;
		std::map<size_t, Qt3DCore::QEntity*> Points;
	};
}