#pragma once

#include "CHexViewer.h"
#include <imgui.h>
#include "imgui_memory_editor.h"
struct sMaze;

#define MKTAG(a0,a1,a2,a3) ((uint32_t)((a3) | ((a2) << 8) | ((a1) << 16) | ((a0) << 24)))
#define MKTAG16(a0,a1) ((uint16_t)((a1) | ((a0) << 8)))

namespace SmitED
{
	class CMazViewer : public SmitED::CHexViewer
	{
	public:
		CMazViewer();
		void update() override;

		virtual void OnDataSet(void);

	protected:
	
	private:
		sMaze *pMaz;
};
}