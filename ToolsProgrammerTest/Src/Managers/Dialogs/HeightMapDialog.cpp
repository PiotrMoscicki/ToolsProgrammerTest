#include "HeightMapDialog.hpp"

#include <QtWidgets/qfiledialog.h>

using namespace TPT;

// ************************************************************************************************
const QPixmap* HeightMapDialog::LoadHeightMap(ISceneManager* scene)
{
	Reset();

	QFileDialog fileDialog;
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setNameFilter("*.png");

	if (fileDialog.exec() != QDialog::Accepted)
		return nullptr;

	auto pixmap = std::make_unique<QPixmap>(
		QPixmap(fileDialog.selectedFiles()[0]).scaled(256, 256, Qt::KeepAspectRatio));
	auto result = pixmap.get();
	scene->SetGeightMap(std::move(pixmap));

	CanceledFlag = false;

	return result;
}

// ************************************************************************************************
void HeightMapDialog::Reset()
{
	CanceledFlag = true;
}
