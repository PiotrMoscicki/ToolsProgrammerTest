#pragma once

#include <vector>

#include "Managers/IInspectorManager.hpp"

namespace TPT
{
	class InspectorManager : public IInspectorManager
	{
	public:
		InspectorManager();

		void SetSceneManager(ISceneManager* sceneManager) override { SceneManager = sceneManager; }
		void SetPointDialog(std::unique_ptr<IPointDialog> pointDialog) override 
			{ PointDialog = std::move(pointDialog); }
		void SetHeightMapDialog(std::unique_ptr<IHeightMapDialog> heightMapDialog) override
			{ HeightMapDialog = std::move(heightMapDialog); }
		virtual void SetSceneResolutionDialog(std::unique_ptr<ISceneResolutionDialog> sceneResolutionDialog) override
			{ SceneResolutionDialog = std::move(sceneResolutionDialog); }

		void AddInspector(std::unique_ptr<IInspector> inspector) override 
			{ inspector->SetManager(this); Inspectors.push_back(std::move(inspector)); }


		virtual const QPixmap* GetHeightMap() override;
		virtual const std::vector<Point*>& GetPoints() override;
		virtual const Point* GetSelectedPoint() override { return SelectedPoint; }


		void SpawnPoint() override;
		void DestroyPoint() override;
		void SelectPoint(size_t id) override;
		void DeselectPoint() override;
		void ModifyPoint(std::unique_ptr<IPointModificationCommand> cmd) override;

		void LoadHeightMap() override;
		void ChangeSceneResolution() override;

	private:
		std::unique_ptr<IPointDialog> PointDialog;
		std::unique_ptr<IHeightMapDialog> HeightMapDialog;
		std::unique_ptr<ISceneResolutionDialog> SceneResolutionDialog;
		std::vector<std::unique_ptr<IInspector>> Inspectors;

		ISceneManager* SceneManager = nullptr;

		Point* SelectedPoint = nullptr;
	
	private slots:
		void HeightMapLoaded(const QPixmap* heightMap);
		void SceneResolutionChanged(SceneResolution resolution, SceneResolution oldResolution);
	};
}