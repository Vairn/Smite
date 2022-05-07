#include "CShapeViewer.h"
#include <imgui.h>
#include <sstream>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include "..\..\sGFX.h"

SmitED::CShapeViewer::CShapeViewer()
{
	currentShape = 0;
}

void SmitED::CShapeViewer::update()
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
	

	//ImGui::EndTabBar();
	//memEdit->DrawContents(pData, uiDataSize);
	end();
}

void SmitED::CShapeViewer::OnDataSet()
{
	// Load the data in.
	auto pGfx = LoadGraphicsFromData(pData);
}

