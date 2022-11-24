#include "CShapeViewer.h"
#include <imgui.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include <vector>
#include <string>
#include <iosfwd>
#include "misc/cpp/imgui_stdlib.h"
#include "../../libSmite/BlitzShape.h"
#include "../../libSmite/common.h"


SmitED::CShapeViewer::CShapeViewer()
{
	m_uiCurrentID = 0;
	

}

void SmitED::CShapeViewer::update()
{
	begin();
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				
				std::vector<std::string> filters = { "Blitz Shape File", "*.*shp" };
				if (ImGui::MenuItem("Load from File"))
				{
					open_file = std::make_shared<pfd::open_file>("Choose Shapes to load ", "C:\\", filters);
				}

				if (ImGui::MenuItem("Save to File"))
				{
					save_file = std::make_shared<pfd::save_file>("Choose Shapes  to save to", "C:\\", filters);
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		if (m_pShapes)
		{

			ImGuiIO& io = ImGui::GetIO();
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
		
			ImGui::SliderInt("Current Sprite", &m_uiCurrentID, 0, m_pShapes->m_vecShapes.size() - 1);
			ImVec2 sp = ImGui::GetCursorScreenPos();
			auto sprite = m_pShapes->m_vecShapes[m_uiCurrentID];
			if (sprite)
			{
				auto width = sprite->width;
				auto height = sprite->height;
				ImVec2 canvas_sz = ImVec2(width * 3, height * 3);
				ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
				const bool is_hovered = ImGui::IsItemHovered(); // Hovered
				const bool is_active = ImGui::IsItemActive();   // Held
				const ImVec2 origin(sp.x, sp.y); // Lock scrolled origin
				const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);
				//std::string sCurrentText = "Current Sprite: ";
				//sCurrentText.append(std::to_string(m_uiCurrentID));
				//ImGui::Text(sCurrentText.c_str());
				//ImGui::SameLine();

				for (auto y = 0; y < height; y++)
				{
					for (auto x = 0; x < width; x++)
					{
						auto index = sprite->chunkyBuffer[(y * width) + x];
						
							ImU32 col = ImGui::GetColorU32(IM_COL32(palette[index].r, palette[index].g, palette[index].b, 255));

							auto st = ImVec2((x * 3), y * 3);
							auto ed = ImVec2((x + 1) * 3, (y + 1) * 3);
							draw_list->AddRectFilled(sp + st, sp + ed, col);
						
					}
				}
			}
			

			display_palette_colors(palette);
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

void SmitED::CShapeViewer::OnDataSet()
{
	// Load the data in.

}

void SmitED::CShapeViewer::DoFileDialog_Open()
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
				if (m_pShapes)
					delete m_pShapes;
				m_pShapes = LoadShapes(result[0].c_str());
				
				pfd::notify("Loading Shapes", "Loading Shape data and Generating Sprites");
				m_pShapes->doPlanarToChunky();
			}
			ifsFile.close();
			m_uiCurrentID = 0;
			palette.clear();

			std::string newfilename = result[0].substr(0, result[0].size() - 3) + "pal";
			/*std::ifstream palFile(newfilename.c_str(), std::ios_base::binary);
			if (palFile.is_open())
			{
				pfd::notify("Loading Palette", "Found a matching Palette file.");
				uint8_t HDR[4];
				palFile >> HDR[0];
				palFile >> HDR[1];
				palFile >> HDR[2];
				palFile >> HDR[3];
				uint8_t size;
				palFile >> size; palFile >> size; palFile >> size; palFile >> size;
				//palFile >> size;
				size /= 3;
				stdc::cout << HDR[0] << HDR[1] << HDR[2] << HDR[3] << "\n";
			for(index=0;index<size;index++)
				{
					rgba_color col;
					palFile >> col.r;
					palFile >> col.g;
					palFile >> col.b;
					std::cout << "Added Colour " << std::to_string(col.r) << " " << std::to_string(col.g) << " " << std::to_string(col.b) << "\n";
					palette.emplace_back(col); 
					//index++;
				}
			}*/
			FILE* fp;
			fopen_s(&fp, newfilename.c_str(), "rb");
			if(fp != nullptr)
			{ 
			fseek(fp, 0, SEEK_END);
			int fsize = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			
				uint32_t count;
				fseek(fp, 4, SEEK_SET);
				fread(&count, 4, 1, fp);
				count  = swap_uint32(count);
				count /= 3;
				int index=0;
				for (index = 0; index < count; index++)
				{
					rgba_color col;
					/*palFile >> col.r;
					palFile >> col.g;
					palFile >> col.b;
					*/
					fread(&col, 3, 1, fp);
					std::cout << "Added Colour " << std::to_string(col.r) << " " << std::to_string(col.g) << " " << std::to_string(col.b) << "\n";
					palette.emplace_back(col);
					//index++;
				}
			}
			else
			{
				//int r, g, b;
				//rgba_color black;
				//black.r = 0; black.g = 0; black.b = 0;

				//rgba_color white;
				//white.r = 255; white.g = 255; white.b = 255;
				//for (r = 0; r <= 255; r += 42) {
				//	
				//	for (g = 0; g <= 255; g += 42) {
				//		for (b = 0; b <= 255; b += 42) {
				//			rgba_color col;
				//			col.r = r;
				//			col.b = b;
				//			col.g = g;
				//			/*if (r * r + g * g + b * b < 50000)
				//				palette.emplace_back(white);
				//			else
				//				palette.emplace_back(black);*/

				//			palette.emplace_back(col);
				//		}
				//	}
				//	
				//}
				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						uint32_t c32 = j* 16 + i;
						
						rgba_color c;
						c.r = c32;
						c.g = c32;
						c.b = c32;
						palette.emplace_back(c);
					}
				}
			}
 			//palFile.close();
			
		}
		//std::cout << "Opened file " << result[0] << "\n";
			open_file = nullptr;
	}
}

void SmitED::CShapeViewer::DoFileDialog_Save()
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

