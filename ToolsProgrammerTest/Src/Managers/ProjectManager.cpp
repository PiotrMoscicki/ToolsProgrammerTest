#include "ProjectManager.hpp"

#include "QtGui/qpixmap.h"

using namespace TPT;

// ************************************************************************************************
void ProjectManager::LoadHeightMap(const QString& path)
{
	SceneManager->SetGeightMap(std::move(std::make_unique<QPixmap>(path)));
	emit HeightMapLoadedSignal();
}
