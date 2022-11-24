#include "CMonsterEditor.h"
#include <imgui.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include <vector>
#include <string>
#include <iosfwd>
#include "misc/cpp/imgui_stdlib.h"
#include "../../libSmite/BlitzShape.h"


SmitED::CMonsterEditor::CMonsterEditor()
{
	m_uiCurrentID = 0;
	

}

void SmitED::CMonsterEditor::update()
{
	begin();
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				
				std::vector<std::string> filters = { "Blitz Monster Data File", "*.*mondat" };
				if (ImGui::MenuItem("Load from File"))
				{
					open_file = std::make_shared<pfd::open_file>("Choose Data to load ", "C:\\", filters);
				}

				if (ImGui::MenuItem("Save to File"))
				{
					save_file = std::make_shared<pfd::save_file>("Choose Data to save to", "C:\\", filters);
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		if (m_pShapes)
		{

			ImGuiIO& io = ImGui::GetIO();
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
		
			ImVec2 sp = ImGui::GetCursorScreenPos();
		}
		else
		{
			std::string text = "Load in a sprite sheet to edit.";
			ShowPlaceholder(text);

		}
	end();

	DoFileDialog_Open();
	DoFileDialog_Save();
}

void SmitED::CMonsterEditor::OnDataSet()
{
	// Load the data in.

}

void SmitED::CMonsterEditor::DoFileDialog_Open()
{
	if (open_file && open_file->ready())
	{
		auto result = open_file->result();
		if (!result.empty())
		{
			//ns::debug::write_line("Opened File %s", result[0].c_str());
			std::ifstream ifsFile(result[0].c_str(), std::ios_base::binary);
			if (ifsFile.is_open())
			{
				
			}
			ifsFile.close();
			m_uiCurrentID = 0;
			
		}
		//std::cout << "Opened file " << result[0] << "\n";
			open_file = nullptr;
	}
}

void SmitED::CMonsterEditor::DoFileDialog_Save()
{
	if (save_file && save_file->ready())
	{
		auto result = save_file->result();
		if (!result.empty())
		{
			//m_sScriptText = m_pTextEditor->GetText();
			//ns::debug::write_line("Saved File %s", result.c_str());
			std::stringstream sOut;
			std::ofstream ofsFile(result.c_str(), std::ios_base::binary);

			if (ofsFile.fail())
			{
				//ns::debug::write_line("Error writing to file: %s", result.c_str());
				ofsFile.clear();
			}
			//WriteMazeFile(ofsFile);
			ofsFile.close();
		}

		save_file = nullptr;
	}
}

