#pragma once

#include "CHexViewer.h"
#include <imgui.h>
#include "imgui_memory_editor.h"

namespace SmitED
{
	class CShapeViewer: public SmitED::CHexViewer
	{
	public:
		CShapeViewer();
		void update() override;

		virtual void OnDataSet(void);
	protected:

	};

}