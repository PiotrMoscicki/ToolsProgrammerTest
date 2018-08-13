#include "HeightMapDialog.hpp"

#include <QtWidgets/qfiledialog.h>

#include "Structures/Commands/ChangeHeightMapCommand.hpp"

using namespace TPT;

// ************************************************************************************************
std::unique_ptr<IDialogCommand> HeightMapDialog::LoadHeightMap(ISceneManager* scene)
{
	Reset();

	QFileDialog fileDialog;
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setNameFilter("*.png");

	if (fileDialog.exec() != QDialog::Accepted)
		return nullptr;

	auto pixmap = std::make_unique<QPixmap>(
		QPixmap(fileDialog.selectedFiles()[0]));

	auto cmd = std::make_unique<ChangeHeightMapCommand>(
		scene->GetHeightMap() ? std::move(std::make_unique<QPixmap>(*scene->GetHeightMap())) : nullptr
		, std::move(pixmap), scene);

	CanceledFlag = false;

	return cmd;
}

// ************************************************************************************************
void HeightMapDialog::Reset()
{
	CanceledFlag = true;
}
