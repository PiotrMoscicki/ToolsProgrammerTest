#include "Pch.hpp"


#include "ProjectManager.hpp"

#include "QtGui/qpixmap.h"

using namespace TPT;

// ************************************************************************************************
void ProjectManager::LoadHeightMap(const QString& path)
{
	SceneManager->SetHeightMap(std::move(std::make_unique<QPixmap>(path)));
	emit HeightMapLoadedSignal();
}
