#include "SceneResolutionDialog.hpp"

#include <QtWidgets/qgridlayout.h>

using namespace TPT;

// ************************************************************************************************
SceneResolutionDialog::SceneResolutionDialog()
{
	auto gridLayout = new QGridLayout(this);
	gridLayout->setColumnStretch(0, 1);
	gridLayout->setColumnStretch(1, 1);
	gridLayout->setColumnStretch(2, 1);
	gridLayout->setColumnStretch(3, 1);

	ResolutionLabel = new QLabel(this);
	ResolutionLabel->setText("Resolution");
	gridLayout->addWidget(ResolutionLabel, 0, 0);

	for (int i = 0; i < 3; ++i)
	{
		ResolutionFields[i] = new QLineEdit(this);
		gridLayout->addWidget(ResolutionFields[i], 0, i + 1);
	}

	connect(ResolutionFields[0], &QLineEdit::editingFinished, this, &SceneResolutionDialog::XChanged);
	connect(ResolutionFields[2], &QLineEdit::editingFinished, this, &SceneResolutionDialog::ZChanged);

	OkButton = new QPushButton(this);
	OkButton->setText("Ok");
	connect(OkButton, &QPushButton::clicked, this, &SceneResolutionDialog::Ok);
	gridLayout->addWidget(OkButton, 1, 3);

	CancelButton = new QPushButton(this);
	CancelButton->setText("Cancel");
	connect(CancelButton, &QPushButton::clicked, this, &SceneResolutionDialog::Cancel);
	gridLayout->addWidget(CancelButton, 1, 0);
}

// ************************************************************************************************
SceneResolution SceneResolutionDialog::SetSceneResolution(ISceneManager* scene)
{
	Reset();

	ResolutionFields[0]->setText(QString::number(scene->GetSceneResolution().X));
	ResolutionFields[1]->setText(QString::number(scene->GetSceneResolution().Y));
	ResolutionFields[2]->setText(QString::number(scene->GetSceneResolution().Z));

	CurrentResolution = scene->GetSceneResolution();

	exec();

	if (CanceledFlag)
		return scene->GetSceneResolution();

	auto resolution = SceneResolution();
	resolution.X = ResolutionFields[0]->text().toInt();
	resolution.Y = ResolutionFields[1]->text().toInt();
	resolution.Z = ResolutionFields[2]->text().toInt();

	scene->SetSceneResolution(resolution);

	return resolution;
}

// ************************************************************************************************
void SceneResolutionDialog::Reset()
{
	CanceledFlag = true;

	ResolutionFields[0]->setText("");
	ResolutionFields[1]->setText("");
	ResolutionFields[2]->setText("");
}




//		private slots
// ************************************************************************************************
void SceneResolutionDialog::Ok()
{
	CanceledFlag = false;

	close();
}

// ************************************************************************************************
void SceneResolutionDialog::Cancel()
{
	close();
}

// ************************************************************************************************
void TPT::SceneResolutionDialog::XChanged()
{
	auto x = ResolutionFields[0]->text().toInt();
	auto k = (float)CurrentResolution.Z / CurrentResolution.X;
	ResolutionFields[2]->setText(QString::number(k * x));
}

// ************************************************************************************************
void TPT::SceneResolutionDialog::ZChanged()
{
	auto z = ResolutionFields[2]->text().toInt();
	auto k = (float)CurrentResolution.X / CurrentResolution.Z;
	ResolutionFields[0]->setText(QString::number(k * z));
}
