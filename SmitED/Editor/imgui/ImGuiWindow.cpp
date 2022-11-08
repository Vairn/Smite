#include "ImGuiWindow.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

SmitED::ImGuiWindow::ImGuiWindow()
	: show(true)
{
	WindowName("Base Window");
}

SmitED::ImGuiWindow::~ImGuiWindow()
{

}

void SmitED::ImGuiWindow::update()
{
	begin();
	end();
}

void SmitED::ImGuiWindow::ShowPlaceholder(std::string& text)
{
	ImVec2 origin = ImGui::GetCursorScreenPos();
	ImVec2 size = origin + ImGui::GetContentRegionAvail();
	
	ImGuiIO& io = ImGui::GetIO();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	draw_list->AddRectFilled(origin, size, IM_COL32(4, 16, 32, 255));



	//	SetCursorCenteredText(origin + (size / 2), text);
	ImGui::TextColored({ 16.f / 255.f, 64.f / 255.f, 128.f / 255.f, 1.f }, text.c_str());
}

void SmitED::ImGuiWindow::display_palette_colors(color_palette const& palette)
{
	auto const origin = ImGui::GetCursorScreenPos();
	auto end = origin + palette_sz;

	ImGuiIO& io = ImGui::GetIO();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 color_p0 = origin;
	auto count = 0;
	for (auto const& color : palette)
	{
		auto offset = ImVec2
		{
			color_p0.x + ((fmodf(count, colors_per_run)) * color_sz),
			color_p0.y + (floorf(count / colors_per_col) * color_sz)
		};

		draw_list->AddRectFilled(offset, { offset.x + color_sz, offset.y + color_sz }, IM_COL32(color.r, color.g, color.b, 255));
		count++;

		if (count >= 256) break;
	}

	// Reset the cursor position
	ImGui::SetCursorScreenPos({ origin.x, origin.y + palette_sz.y + 8 });
}


bool SmitED::ImGuiWindow::begin()
{
	return ImGui::Begin(sWindowName.c_str(), &show, ImGuiWindowFlags_MenuBar);
}

void SmitED::ImGuiWindow::end()
{
	ImGui::End();
}

