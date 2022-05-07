#pragma once

#include "CHexViewer.h"
#include <imgui.h>
#include "imgui_memory_editor.h"
typedef struct _tSHP tSHP;
namespace SmitED
{
	class CShapeViewer: public SmitED::CHexViewer
	{
	public:
		CShapeViewer();
		void update() override;

		virtual void OnDataSet(void);
	protected:

		tSHP* pShapes;
		int currentShape;
	};

}