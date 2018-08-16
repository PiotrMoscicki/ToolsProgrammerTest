#pragma once

#include "Application/Application.hpp"

#include "Dialogs/IDialog.hpp"
#include "Dialogs/HelpDialog.hpp"

#include "Inspectors/IInspector.hpp"
#include "Inspectors/HeightMapInspector.hpp"
#include "Inspectors/PointInspector.hpp"
#include "Inspectors/Scene3DInspector.hpp"
#include "Inspectors/SceneInspector.hpp"

#include "Managers/Dialogs/IHeightMapDialog.hpp"
#include "Managers/Dialogs/IPointDialog.hpp"
#include "Managers/Dialogs/ISceneResolutionDialog.hpp"
#include "Managers/Dialogs/HeightMapDialog.hpp"
#include "Managers/Dialogs/PointDialog.hpp"
#include "Managers/Dialogs/SceneResolutionDialog.hpp"

#include "Managers/ICommandsManager.hpp"
#include "Managers/IProjectManager.hpp"
#include "Managers/IInspectorManager.hpp"
#include "Managers/ISceneManager.hpp"

#include "Structures/Point.hpp"
#include "Structures/SceneResolution.hpp"

#include "Structures/Commands/ICommand.hpp"
#include "Structures/Commands/IDialogCommand.hpp"
#include "Structures/Commands/IPointModificationCommand.hpp"
#include "Structures/Commands/BlankCommand.hpp"
#include "Structures/Commands/ChangeHeightMapCommand.hpp"
#include "Structures/Commands/ChangeSceneResolutionCommand.hpp"
#include "Structures/Commands/SpawnPointsCommand.hpp"
#include "Structures/Commands/PointModificationCommand.hpp"
#include "Structures/Commands/DestroyPointCommand.hpp"
