#pragma once

#include "Managers/ISceneManager.hpp"
#include "Structures/Point.hpp"

namespace TPT
{
	class SceneManager : public ISceneManager
	{
	public:
		void SetHeightMap(std::unique_ptr<QPixmap> heightMap) override;
		QPixmap* GetHeightMap() override { return HeightMap.get(); }

		Point* SpawnPoint() override;
		Point* SpawnPoint(size_t id) override;
		void DestroyPoint(size_t id) override;
		Point* GetPoint(size_t id) override;
		std::vector<Point*> GetPoints() override { return Points; }

		size_t GetSceneResolutionX() override { return SceneResolutionX; }
		size_t GetSceneResolutionY() override { return SceneResolutionY; }
		size_t GetSceneResolutionZ() override { return SceneResolutionZ; }

	private:
		std::unique_ptr<QPixmap> HeightMap;
		std::vector<Point*> Points;

		size_t SceneResolutionX = 255;
		size_t SceneResolutionY = 255;
		size_t SceneResolutionZ = 255;
	};
}