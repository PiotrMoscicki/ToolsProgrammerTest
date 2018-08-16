#pragma once

#include <QtWidgets/qwidget.h>

#include "Inspectors/IInspector.hpp"
#include "Structures/Point.hpp"

class QMenu;
class QAction;
class QResizeEvent;
class QPixmap;
class QLabel;

namespace TPT
{
	class IInspectorManager;

	class HeightMapInspector : public IInspector, public QWidget
	{
	public:
		HeightMapInspector(QWidget* parent);

		void SetManager(IInspectorManager* manager) override;

	public slots:
		void HeightMapLoaded(const QPixmap* heightMap);

	private:
		IInspectorManager* Manager = nullptr;
		const QPixmap* HeightMap = nullptr;

		QLabel* Image;

		QMenu* ContextMenu;
			QAction* LoadHeightMapAction;

		void resizeEvent(QResizeEvent* e) override;

	private slots:
		void SpawnContextMenu(QPoint pos);
			void LoadHeightMap();
	};
}