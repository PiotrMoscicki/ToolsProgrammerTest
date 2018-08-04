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
			{ inspector->SetManager(this); Inspectors.push_back(inspector); }


		QVector3D* GetSelectedPoint() override { return SelectedPoint; }


		QVector3D* SpawnPoint() override;
		void Destroypoint() override;
		void SelectPoint(QVector3D* point) override;
		void ModifyPoint() override;

	public slots:
		void HeightMapLoaded() override;

	private:
		std::unique_ptr<IPointDialog> PointDialog;
		std::vector<std::unique_ptr<IInspector>> Inspectors;

		IProjectManager* ProjectManager = nullptr;

		QVector3D* SelectedPoint = nullptr;
	};
}