#include "CMazViewer.h"

SmitED::CMazViewer::CMazViewer()
{
	
}

void SmitED::CMazViewer::update()
{
	begin();
	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Maze"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Level Script"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Wall Set"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Maze"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("HexView"))
		{
			
			memEdit->DrawContents(pData, uiDataSize);
		}

		ImGui::EndTabBar();
	}
	//memEdit->DrawContents(pData, uiDataSize);
	end();
}

void SmitED::CMazViewer::OnDataSet()
{

}

