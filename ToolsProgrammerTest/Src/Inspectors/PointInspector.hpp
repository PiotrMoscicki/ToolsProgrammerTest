#pragma once

#include <QtWidgets/qwidget.h>

#include "Inspectors/IInspector.hpp"

class QLabel;
class QLineEdit;

namespace TPT
{
	class Point;
	class IInspectorManager;

	class PointInspector : public IInspector, public QWidget
	{
	public:
		PointInspector(QWidget* parent);

		void SetManager(IInspectorManager* manager) override;

	public slots:
		void PointSelected(const Point* point);
		void PointModified(const Point* point);

		void HeightMapLoaded(const QPixmap* heightMap);

	private:
		IInspectorManager* Manager = nullptr;

		QLabel* NameLabel;		QLineEdit* NameField;
		QLabel* IdLabel;		QLineEdit* IdField;
		QLabel* PositionLabel;	QLineEdit* PositionFields[3];

	private slots:
		void FieldModified();
	};
}