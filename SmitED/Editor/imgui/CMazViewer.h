#pragma once

#include "CHexViewer.h"
#include <imgui.h>
#include "imgui_memory_editor.h"

#define MKTAG(a0,a1,a2,a3) ((uint32_t)((a3) | ((a2) << 8) | ((a1) << 16) | ((a0) << 24)))
#define MKTAG16(a0,a1) ((uint16_t)((a1) | ((a0) << 8)))


struct sMaze
{
	uint8_t walldata[32][32];
	uint8_t coldata[32][32];
};
namespace SmitED
{
	class CMazViewer : public SmitED::CHexViewer
	{
	public:
		CMazViewer();
		void update() override;

		virtual void OnDataSet(void);
	protected:
};
}