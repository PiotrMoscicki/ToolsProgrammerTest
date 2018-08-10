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

		void SetSceneResolution(SceneResolution resolution) override { Resolution = resolution; }

		SceneResolution GetSceneResolution() override { return Resolution; }

	private:
		std::unique_ptr<QPixmap> HeightMap;
		std::vector<Point*> Points;

		SceneResolution Resolution;
	};
}