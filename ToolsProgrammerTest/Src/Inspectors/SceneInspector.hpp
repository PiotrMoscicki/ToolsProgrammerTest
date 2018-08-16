#pragma once

#include <QtWidgets/qwidget.h>

#include "Inspectors/IInspector.hpp"

class QMenu;
class QAction;
class QTreeWidget;
class QTreeWidgetItem;

namespace TPT
{
	class IInspectorManager;
	class Point;

	class SceneInspector : public IInspector, public QWidget
	{
	public:
		SceneInspector(QWidget* parent);

		void SetManager(IInspectorManager* manager) override;

	public slots:
		void PointSpawned(const Point* point);
		void PointDestroyed(const Point* point);
		void PointSelected(const Point* point);
		void PointModified(const Point* point);

	private:
		IInspectorManager* Manager = nullptr;
		std::map<QTreeWidgetItem*, const Point*> ItemToPoint;
		std::map<const Point*, QTreeWidgetItem*> PointToItem;

		QTreeWidget* Tree;

		bool SilenceSelectionChanged = false;
		bool SilenceItemChanged = false;

		QMenu* ContextMenu;
			QAction* SpawnPointAction;
			QAction* DestroyPointAction;

	private slots:
		void SelectionChanged();
		void FieldModified();

		void SpawnContextMenu(QPoint pos);
			void SpawnPoint();
			void DestroyPoint();
	};
}