#pragma once

#include "CHexViewer.h"
#include <imgui.h>
#include "imgui_memory_editor.h"

namespace SmitED
{
	class CWallViewer : public SmitED::CHexViewer
	{
	public:
		CWallViewer();
		void update() override;

		virtual void OnDataSet(void);
	protected:

	};

}