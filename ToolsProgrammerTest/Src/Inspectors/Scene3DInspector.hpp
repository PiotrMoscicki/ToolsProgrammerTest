#pragma once

#include <QtWidgets/qwidget.h>

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
		void PointSelected(const Point* point);

	private:
		IInspectorManager* Manager = nullptr;
	};
}