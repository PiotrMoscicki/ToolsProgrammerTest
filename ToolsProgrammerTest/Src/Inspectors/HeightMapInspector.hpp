#pragma once

#include <QtWidgets/qmenu.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>

#include "Inspectors/IInspector.hpp"
#include "Managers/IInspectorManager.hpp"

namespace TPT
{
	class HeightMapInspector : public IInspector, public QWidget
	{
	public:
		HeightMapInspector(QWidget* parent);

		void SetManager(IInspectorManager* manager) override;

	public slots:
		void HeightMapLoaded(const QPixmap* heightMap);

		void Update();
		void Reload();

	private:
		IInspectorManager* Manager = nullptr;

		QLabel* Image;

		QMenu* ContextMenu;
			QAction* LoadHeightMapAction;

	private slots:
		void SpawnContextMenu(QPoint pos);
			void LoadHeightMap();
	};
}