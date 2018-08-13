#pragma once

#include <QtWidgets/qwidget.h>

#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/qpickevent.h>

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

	private:
		class PickHelper : public QObject
		{
		public:
			PickHelper(Scene3DInspector* owner, size_t pointId) : Owner(owner), PointId(pointId) {}

			void PickEvent(Qt3DRender::QPickEvent* pick) { Owner->Manager->SelectPoint(PointId); }

		private:
			Scene3DInspector* Owner;
			size_t PointId;
		};

		IInspectorManager* Manager = nullptr;
		
		Qt3DCore::QEntity* Root;
		std::map<size_t, Qt3DCore::QEntity*> Points;
		std::map<size_t, Qt3DExtras::QPhongMaterial*> Materials;
		std::map<size_t, Qt3DCore::QTransform*> Transforms;
		std::map<size_t, std::unique_ptr<PickHelper>> PickHelpers;

		bool AnySelected = false;
		size_t SelectedPioint;
		QColor LastSelectedColor;
	};
}