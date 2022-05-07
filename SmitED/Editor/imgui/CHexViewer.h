#pragma once

#include "ImGuiWindow.h"
#include <imgui.h>
#include "imgui_memory_editor.h"

#define MKTAG(a0,a1,a2,a3) ((uint32_t)((a3) | ((a2) << 8) | ((a1) << 16) | ((a0) << 24)))
#define MKTAG16(a0,a1) ((uint16_t)((a1) | ((a0) << 8)))

namespace SmitED
{
	class CPak;

	class CHexViewer : public SmitED::ImGuiWindow
	{
	public:
		CHexViewer();
		void update() override;

		void SetData(std::string _sName, uint8_t* _pData, uint32_t _uiSize) override;

		virtual void OnDataSet(void) {}
		void SetPakFile(CPak* second);
	protected:

		std::string sSelectedFilename;
		uint8_t* pData;
		uint32_t uiDataSize;
		MemoryEditor* memEdit;


		CPak* pSourcePak;
	};
}