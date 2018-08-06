#pragma once

#include <vector>

#include "Managers/IInspectorManager.hpp"

namespace TPT
{
	class Inspectormanager : public IInspectorManager
	{
	public:
		void SetProjectManager(IProjectManager* projectManager) override { ProjectManager = projectManager; }
		void SetPointDialog(std::unique_ptr<IPointDialog> pointDialog) override 
			{ PointDialog = std::move(pointDialog); }

		void AddInspector(std::unique_ptr<IInspector> inspector) override 
			{ inspector->SetManager(this); Inspectors.push_back(std::move(inspector)); }


		virtual const QImage* GetHeightMap() override;
		virtual const std::vector<Point*>& GetPoints() override;
		virtual const Point* GetSelectedPoint() override { return SelectedPoint; }


		void SpawnPoint() override;
		void DestroyPoint() override;
		void SelectPoint(size_t id) override;
		void ModifyPoint(std::unique_ptr<IPointModificationCommand> cmd) override;

	public slots:
		void HeightMapLoaded() override;

	private:
		std::unique_ptr<IPointDialog> PointDialog;
		std::vector<std::unique_ptr<IInspector>> Inspectors;

		IProjectManager* ProjectManager = nullptr;

		Point* SelectedPoint = nullptr;
	};
}