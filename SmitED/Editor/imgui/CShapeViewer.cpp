#include "CShapeViewer.h"
#include <imgui.h>
#include <sstream>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

SmitED::CShapeViewer::CShapeViewer()
{
	//currentShape = 0;
}

void SmitED::CShapeViewer::update()
{
	begin();
	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Graphics"))
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			const ImVec2 sp = ImGui::GetCursorScreenPos();
			for (int y = 0; y < 200; y++)
			{
				for (int x = 0; x < 320; x++)
				{
					//auto p = pCPS->_pal._data[pCPS->_bitmap->pData[y * 320 + x]];
					//U32 col = p.r << 24 | p.g << 16 | p.b << 8 | 0x0F;
					//ImU32 col = ImGui::GetColorU32(IM_COL32(p.r, p.g, p.b, 255));
					//auto st = ImVec2((x * 3), y * 3);
					//auto ed = ImVec2((x + 1) * 3, (y + 1) * 3);
					//draw_list->AddRectFilled(sp + st, sp + ed, col);
				}
			}
			ImGui::Dummy(ImVec2(320, 200));
			//ImGui::PopItemWidth();


			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Palette"))
		{
			
			ImGui::EndTabItem();

		}

		if (ImGui::BeginTabItem("HexView"))
		{
			memEdit->DrawContents(pData, uiDataSize);
			ImGui::EndTabItem();
		}
	
		ImGui::EndTabBar();
	}
	

	//ImGui::EndTabBar();
	//memEdit->DrawContents(pData, uiDataSize);
	end();
}

void SmitED::CShapeViewer::OnDataSet()
{
	// Load the data in.

}

