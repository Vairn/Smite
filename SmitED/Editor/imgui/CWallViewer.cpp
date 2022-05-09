#include "CWallViewer.h"
#include <imgui.h>
#include <sstream>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

SmitED::CWallViewer::CWallViewer()
{
	//currentShape = 0;
}

void SmitED::CWallViewer::update()
{
	begin();
	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Graphics"))
		{
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
	if (ImGui::Button("Import"))
	{
		
	}

	//ImGui::EndTabBar();
	//memEdit->DrawContents(pData, uiDataSize);
	end();
}

void SmitED::CWallViewer::OnDataSet()
{
	// Load the data in.


}

