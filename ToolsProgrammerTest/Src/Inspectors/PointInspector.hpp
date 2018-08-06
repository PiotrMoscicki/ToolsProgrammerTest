#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>

#include "Inspectors/IInspector.hpp"
#include "Managers/IInspectorManager.hpp"

namespace TPT
{
	class PointInspector : public IInspector, public QWidget
	{
	public:
		PointInspector(QWidget* parent);

		void SetManager(IInspectorManager* manager) override;

	public slots:
		void PointSelected(const Point* point);
		void PointModified(const Point* point);

		void Update();
		void Reload();

	private:
		IInspectorManager* Manager = nullptr;

		QLabel* NameLabel;		QLineEdit* NameField;
		QLabel* PositionLabel;	QLineEdit* PositionFields[3];

	private slots:
		void FieldModified();
	};
}