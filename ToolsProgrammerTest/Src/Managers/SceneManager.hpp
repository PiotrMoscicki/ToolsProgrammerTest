#pragma once

#include "Managers/ISceneManager.hpp"

namespace TPT
{
	class SceneManager : public ISceneManager
	{
	public:
		void SetHeightMap(std::unique_ptr<QPixmap> heightMap) override;
		QPixmap* GetHeightMap() override { return HeightMap.get(); }

		void SetScene(std::unique_ptr<Scene> scene) override { Scene = std::move(scene); }
		Scene* GetScene() override { return Scene.get(); }

		Point* SpawnPoint() override;
		Point* SpawnPoint(size_t id) override;
		void DestroyPoint(size_t id) override;

	private:
		std::unique_ptr<QPixmap> HeightMap;
		std::unique_ptr<Scene> Scene;
	};
}