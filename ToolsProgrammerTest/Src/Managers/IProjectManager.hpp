#pragma once

#include <QtCore/qstring.h>

namespace TPT
{
	class IProjectManager
	{
	public:
		virtual void SetInspectorManager() = 0;

		virtual void LoadHeightMap(const QString& path) = 0;
	};
}