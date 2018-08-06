#pragma once

#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class SceneManager : public ISceneManager
	{
	public:
		void SetGeightMap(std::unique_ptr<QPixmap> heightMap) override { HeightMap = std::move(heightMap); }
		QPixmap* GetHeightMap() override { return HeightMap.get(); }

		void SetScene(std::unique_ptr<Scene> scene) override { Scene = std::move(scene); }
		Scene* GetScene() override { return Scene.get(); }

		const Point* SpawnPoint() override;
		const Point* SpawnPoint(size_t id) override;
		void DestroyPoint(size_t id) override;

	private:
		std::unique_ptr<QPixmap> HeightMap;
		std::unique_ptr<Scene> Scene;
	};
}