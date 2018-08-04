#include "ProjectManager.hpp"

#include "QtGui/qimage.h"

using namespace TPT;

void ProjectManager::LoadHeightMap(const QString& path)
{
	SceneManager->SetGeightMap(std::move(std::make_unique<QImage>(path)));
	emit HeightMapLoadedSignal();
}
