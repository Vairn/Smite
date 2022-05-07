#pragma once
#include <string>
#include <imgui.h>

namespace SmitED
{
	class ImGuiUIManager;

	class ImGuiWindow
	{
	public:
		ImGuiWindow();
		~ImGuiWindow();
		virtual void update();
		bool Show() const { return show; }
		void Show(bool val) { show = val; }
		const std::string& GetName() { return sWindowName; };
		void SetManager(SmitED::ImGuiUIManager* pManager) { pOwner = pManager; }

		virtual void SetData(std::string _sName, uint8_t* _pData, uint32_t _uiSize) {}
		
	protected:
		void WindowName(std::string val) { sWindowName = val; }
		virtual bool begin();
		void end();
		bool show;

		SmitED::ImGuiUIManager* pOwner;

		std::string sWindowName;
	};
}