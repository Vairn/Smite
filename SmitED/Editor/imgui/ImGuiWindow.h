#pragma once
#include <string>
#include <imgui.h>
#include <vector>

namespace SmitED
{
	class ImGuiUIManager;
	
	auto constexpr color_sz = 16.f;
	auto constexpr colors_per_run = 16.f;
	auto constexpr color_run_width = color_sz * colors_per_run;
	auto constexpr colors_per_col = 256.f / colors_per_run;
	auto constexpr palette_sz = ImVec2{ color_run_width, color_run_width };
	struct rgba_color
	{
		uint8_t r{ 0 };
		uint8_t g{ 0 };
		uint8_t b{ 0 };
		uint8_t a{ 255 };
		operator uint32_t() { return a << 24 | r << 16 | g << 8 | static_cast<uint32_t>(b); }
		
		rgba_color()
		{
			r = 0; b = 0; g = 0; a = 255;
		}
		rgba_color(uint32_t RGBA) {
			b = (RGBA >> 16) & 0xFF;
			g = (RGBA >> 8) & 0xFF;
			r = RGBA & 0xFF;
		}
	};

	using color_palette = std::vector<rgba_color>;

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
		void WindowName(std::string val) { sWindowName = val; }
	protected:

		void ShowPlaceholder(std::string& text);
		void display_palette_colors(color_palette const& palette);
	protected:
		
		virtual bool begin();
		void end();
		bool show;

		SmitED::ImGuiUIManager* pOwner;

		std::string sWindowName;
	};
}