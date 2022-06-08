#include "../../libSmite/typeDefs.h"
#include "../../libSmite/IScriptCommand.h"

#include "CMazViewer.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
SmitED::CMazViewer::CMazViewer()
{
	pTextEditor = new TextEditor();
	auto lang = TextEditor::LanguageDefinition::CPlusPlus();
	pTextEditor->SetLanguageDefinition(lang);
	pMaz = new sMaze();
}

void SmitED::CMazViewer::update()
{
	begin();
	auto cpos = pTextEditor->GetCursorPosition();


	//ImGui::BeginChild("Script");//("SCRIPT", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
	//ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
	DrawMenuBar();
	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Maze 2D"))
		{
			ImGuiIO& io = ImGui::GetIO();
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ImVec2 sp = ImGui::GetCursorScreenPos();
			ImVec2 canvas_sz = ImVec2(32 * 15, 32 * 15);
			ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
			const bool is_hovered = ImGui::IsItemHovered(); // Hovered
			const bool is_active = ImGui::IsItemActive();   // Held
			const ImVec2 origin(sp.x, sp.y); // Lock scrolled origin
			const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);
			int mapX = 0;
			int mapY = 0;
			if (is_hovered)
			{
				//points.push_back(mouse_pos_in_canvas);
				//points.push_back(mouse_pos_in_canvas);
				//adding_line = true;
				mapX = mouse_pos_in_canvas.x / 15;
				mapY = mouse_pos_in_canvas.y / 15;
				if (mapX < 32)
				{
					int offset = mapY * 32 + mapX;

					if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
						pMaz->walldata[offset] = 0b01010101;
					if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
						pMaz->walldata[offset] = 0b10101010;
					if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
						pMaz->walldata[offset] = 0x00;

				}
			}

			draw_list->AddRectFilled(sp+ImVec2(0, 0), sp+ImVec2(32*15, 32*15), 0xf0343434);
			for (int y = 0; y < 32; y++)
			{
				for (int x = 0; x < 32; x++)
				{
					int offset = (y * 32) + x;
					int wmi = pMaz->walldata[offset];
					uint8_t n, s, e, w;
					uint32_t colN, colS, colE, colW;
					colN = colE = colS = colW = 0x7f7f7f7f;

					n = 0b00000011 & (wmi);
					e = 0b00000011 & (wmi >> 2);
					s = 0b00000011 & (wmi >> 4);
					w = 0b00000011 & (wmi >> 6);
					int16_t drawDoor = 0x0000;
					if (n == 1)	colN = 0xFFFFFFFF;
					if (e == 1)	colE = 0xFFFFFFFF;
					if (s == 1)	colS = 0xFFFFFFFF;
					if (w == 1)	colW = 0xFFFFFFFF;

					if (n == 2) { colN = 0xFF7f7f7f; drawDoor += 0x01; }
					if (e == 2) { colE = 0xFF7f7f7f; drawDoor += 0x02; }
					if (s == 2) { colS = 0xFF7f7f7f; drawDoor += 0x04; }
					if (w == 2) { colW = 0xFF7f7f7f;  drawDoor += 0x08; }

					if (n == 3)	colN = 0xFF7f7fFF;
					if (e == 3)	colE = 0xFF7f7fFF;
					if (s == 3)	colS = 0xFF7f7fFF;
					if (w == 3)	colW = 0xFF7f7fFF;


					draw_list->AddLine(sp + ImVec2(x* 15, y* 15), sp + ImVec2((x + 1)* 15, y* 15), colN, 1);					
					draw_list->AddLine(sp + ImVec2(x* 15, y* 15), sp + ImVec2((x* 15), (1 + y)* 15), colE, 1);				
					draw_list->AddLine(sp + ImVec2(x* 15, (1 + y)* 15), sp + ImVec2(((1 + x)* 15), (1+y)* 15), colS, 1);					
					draw_list->AddLine(sp + ImVec2((1 + x)* 15, y* 15), sp + ImVec2(((1 + x)* 15), (1 + y)* 15), colW, 1);
					
					ImVec2 dl = ImVec2(4, -5);
					ImVec2 dr = ImVec2(-4, 5);

					if (drawDoor & 0x01)
						draw_list->AddRect(dl + sp + ImVec2(x * 15, y * 15), dr + sp + ImVec2((x + 1) * 15, y * 15), colN);
					if (drawDoor & 0x02)
						draw_list->AddRect(dr + sp + ImVec2(x * 15, y * 15), dl + sp + ImVec2((x * 15), (1 + y) * 15), colE);
					if (drawDoor & 0x04)
						draw_list->AddRect(dl + sp + ImVec2(x * 15, (1 + y) * 15), dr + sp + ImVec2(((1 + x) * 15), (1 + y) * 15), colS);
					if (drawDoor & 0x08)
						draw_list->AddRect(dr + sp + ImVec2((1 + x) * 15, y * 15), dl + sp + ImVec2(((1 + x) * 15), (1 + y) * 15), colW);

					//auto p = pCPS->_pal._data[pCPS->_bitmap->pData[y * 320 + x]];
					//U32 col = p.r << 24 | p.g << 16 | p.b << 8 | 0x0F;
					//draw_list->AddRectFilled(sp + st, sp + ed, col);
					//draw_list->AddLine(sp, sp+ImVec2(20,30), col);
					
				}
			}
			
			//ImGui::Dummy(ImVec2(65*15, 32*15));
			
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Level Script"))
		{
			ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, pTextEditor->GetTotalLines(),
				pTextEditor->IsOverwrite() ? "Ovr" : "Ins",
				pTextEditor->CanUndo() ? "*" : " ",
				pTextEditor->GetLanguageDefinition().mName.c_str(), "");
			pTextEditor->Render("TextEditor");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Maze 3D"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Wall Set"))
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

void SmitED::CMazViewer::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Compile"))
			{
				auto textToSave = pTextEditor->GetText();
				/// save text....
				//m_pScriptOwner->GetAttribute("Script")->SetRawValueAs<std::string>(textToSave);
				//pEditorAttribute->SetRawValueAs<std::string>(textToSave);
			}
			std::vector<std::string> filters = { "Python Script", "*.py" };
			if (ImGui::MenuItem("Load from File"))
			{
				open_file = std::make_shared<pfd::open_file>("Choose Script to load from", "C:\\", filters);
			}

			if (ImGui::MenuItem("Save to File"))
			{
				save_file = std::make_shared<pfd::save_file>("Choose Script to save to", "C:\\", filters);
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			bool ro = pTextEditor->IsReadOnly();
			if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
				pTextEditor->SetReadOnly(ro);
			ImGui::Separator();

			if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && pTextEditor->CanUndo()))
				pTextEditor->Undo();
			if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && pTextEditor->CanRedo()))
				pTextEditor->Redo();

			ImGui::Separator();

			if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, pTextEditor->HasSelection()))
				pTextEditor->Copy();
			if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && pTextEditor->HasSelection()))
				pTextEditor->Cut();
			if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && pTextEditor->HasSelection()))
				pTextEditor->Delete();
			if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
				pTextEditor->Paste();

			ImGui::Separator();

			if (ImGui::MenuItem("Select all", nullptr, nullptr))
				pTextEditor->SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(pTextEditor->GetTotalLines(), 0));

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Dark palette"))
				pTextEditor->SetPalette(TextEditor::GetDarkPalette());
			if (ImGui::MenuItem("Light palette"))
				pTextEditor->SetPalette(TextEditor::GetLightPalette());
			if (ImGui::MenuItem("Retro blue palette"))
				pTextEditor->SetPalette(TextEditor::GetRetroBluePalette());
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();

	}
}

void SmitED::CMazViewer::OnDataSet()
{

}

