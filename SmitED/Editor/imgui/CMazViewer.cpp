#include "../../libSmite/typeDefs.h"
#include "../../libSmite/IScriptCommand.h"

#include "CMazViewer.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
CScriptRoutine* SmitED::CMazViewer::m_pScriptCompiler = nullptr;
int SmitED::CMazViewer::instance = 1;

void SmitED::CMazViewer::LoadMazeFile(std::ifstream& ifsFile)
{
	uint8_t a;
	ifsFile >> a;
	ifsFile >> a;
	ifsFile >> a;
	ifsFile >> a;
	ifsFile >> a;
	pMaz->loadFromFile(ifsFile);
}


void SmitED::CMazViewer::WriteMazeFile(std::ofstream& ofsFile)
{
	ofsFile << "MAZ";
	ofsFile << (uint8_t)1;
	ofsFile << (uint8_t)0;
	pMaz->saveToFile(ofsFile);
}

SmitED::CMazViewer::CMazViewer()
{
	sMazeMonsters[0] = ""; sMazeMonsters[1] = "";
	sMazeWallset = "";
	sMazeDecorations = "";
	pTextEditor = new TextEditor();
	auto lang = LangSmyte();
	pTextEditor->SetLanguageDefinition(lang);
	pMaz = new sMaze();
	instance++;
	WindowName("Maze "+ std::to_string(instance));
	if (m_pScriptCompiler == nullptr)
	{
		m_pScriptCompiler = new CScriptRoutine();

		/*m_pScriptCompiler->addCommand(ENCOUNTER, "Encounter", 1, nullptr, nullptr);
		m_pScriptCompiler->addCommand(IDENTIFY_ITEMS, "IdentifyItems", 2, &encodeIdentifyItems, &decodeIdentifyItems);
		m_pScriptCompiler->addCommand(TURN, "Turn", 2, &encodeTurn, &decodeTurn);
		m_pScriptCompiler->addCommand(LAUNCHER, "Launcher", 5, &encodeLauncher, &decodeLauncher);
		m_pScriptCompiler->addCommand(ADD_ITEM, "AddItem", 4, &encodeAddItem, &decodeAddItem);
		m_pScriptCompiler->addCommand(GIVE_XP, "GiveXp", 1, &encodeGiveXp, &decodeGiveXp);
		m_pScriptCompiler->addCommand(CHANGE_LEVEL, "ChangeLevel", 3, &encodeChangeLevel, &decodeChangeLevel);
		m_pScriptCompiler->addCommand(REMOVE_ITEM, "RemoveItem", 2, &encodeRemoveItem, &decodeRemoveItem);
		m_pScriptCompiler->addCommand(IF, "If", -1, &encodeIf, &decodeIf);
		m_pScriptCompiler->addCommand(GOSUB, "Gosub", 2, &encodeGosub, &decodeGosub);
		m_pScriptCompiler->addCommand(RETURN, "Return", 0, &encodeReturn, &decodeReturn);
		m_pScriptCompiler->addCommand(END, "End", 0, &encodeEnd, &decodeEnd);
		m_pScriptCompiler->addCommand(GOTO, "Goto", 1, &encodeGoto, &decodeGoto);
		m_pScriptCompiler->addCommand(DAMAGE, "Damage", 2, &encodeDamage, &decodeDamage);
		m_pScriptCompiler->addCommand(CLEAR_FLAG, "ClearFlag", 1, &encodeClearFlag, &decodeClearFlag);
		m_pScriptCompiler->addCommand(SOUND, "Sound", 2, &encodeSound, &decodeSound);
		m_pScriptCompiler->addCommand(SET_FLAG, "SetFlag", 1, &encodeSetFlag, &decodeSetFlag);
		m_pScriptCompiler->addCommand(MESSAGE, "Message", 2, &encodeMessage, &decodeMessage);
		m_pScriptCompiler->addCommand(STEAL_ITEM, "StealItem", 4, &encodeStealItem, &decodeStealItem);
		m_pScriptCompiler->addCommand(TELEPORT, "Teleport", 5, &encodeTeleport, &decodeTeleport);
		m_pScriptCompiler->addCommand(ADD_MONSTER, "AddMonster", 14, &encodeAddMonster, &decodeAddMonster);
		m_pScriptCompiler->addCommand(CLOSE_DOOR, "CloseDoor", 2, &encodeCloseDoor, &decodeCloseDoor);
		m_pScriptCompiler->addCommand(OPEN_DOOR, "OpenDoor", 2, &encodeOpenDoor, &decodeOpenDoor);
		m_pScriptCompiler->addCommand(CHANGE_WALL, "ChangeWall", 4, &encodeChangeWall, &decodeChangeWall);
		m_pScriptCompiler->addCommand(SET_WALL, "SetWall", 4, &encodeSetWall, &decodeSetWall);*/

		m_pScriptCompiler->addCommand(ENCOUNTER, "Encounter", 1, nullptr, nullptr);
		m_pScriptCompiler->addCommand(IDENTIFY_ITEMS, "IdentifyItems", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(TURN, "Turn", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(LAUNCHER, "Launcher", 5, nullptr, nullptr);
		m_pScriptCompiler->addCommand(ADD_ITEM, "AddItem", 4, nullptr, nullptr);
		m_pScriptCompiler->addCommand(GIVE_XP, "GiveXp", 1, nullptr, nullptr);
		m_pScriptCompiler->addCommand(CHANGE_LEVEL, "ChangeLevel", 3, nullptr, nullptr);
		m_pScriptCompiler->addCommand(REMOVE_ITEM, "RemoveItem", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(IF, "If", -1, nullptr, nullptr);
		m_pScriptCompiler->addCommand(GOSUB, "Gosub", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(RETURN, "Return", 0, nullptr, nullptr);
		m_pScriptCompiler->addCommand(END, "End", 0, nullptr, nullptr);
		m_pScriptCompiler->addCommand(GOTO, "Goto", 1, nullptr, nullptr);
		m_pScriptCompiler->addCommand(DAMAGE, "Damage", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(CLEAR_FLAG, "ClearFlag", 1, nullptr, nullptr);
		m_pScriptCompiler->addCommand(SOUND, "Sound", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(SET_FLAG, "SetFlag", 1, nullptr, nullptr);
		m_pScriptCompiler->addCommand(MESSAGE, "Message", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(STEAL_ITEM, "StealItem", 4, nullptr, nullptr);
		m_pScriptCompiler->addCommand(TELEPORT, "Teleport", 5, nullptr, nullptr);
		m_pScriptCompiler->addCommand(ADD_MONSTER, "AddMonster", 14, nullptr, nullptr);
		m_pScriptCompiler->addCommand(CLOSE_DOOR, "CloseDoor", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(OPEN_DOOR, "OpenDoor", 2, nullptr, nullptr);
		m_pScriptCompiler->addCommand(CHANGE_WALL, "ChangeWall", 4, nullptr, nullptr);
		m_pScriptCompiler->addCommand(SET_WALL, "SetWall", 4, nullptr, nullptr);
	}
	/*
	AddItem(1, 10,10, 5)
Message(1, "It is very Dusty Here")
GiveXp(1000)
SetFlag(10)
Message(1, "Going Down...")
Sound(1,2)
OpenDoor(10,10)
Message(1, "Going Down...")
SetWall(12,12,4,1)

*/
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
			DrawMaze2D();
			
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
		if (ImGui::BeginTabItem("Level Events"))
		{
			if (ImGui::Button("Add Event"))
			{

			}
			ImGui::EndTabItem();
		}
		
		if (ImGui::BeginTabItem("Level Data"))
		{
			if (ImGui::BeginTabBar("##ldtabs", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("General"))
				{
					ImGui::InputTextWithHint("Wallset", "Wallset Data File", &sMazeWallset, ImGuiInputTextFlags_EnterReturnsTrue);
					ImGui::SameLine();
					if (ImGui::Button("Browse###Wallset"))
					{
					}

					ImGui::InputTextWithHint("Monster Type 1", "Monster Data File", &sMazeMonsters[0], ImGuiInputTextFlags_EnterReturnsTrue);
					ImGui::SameLine();
					if (ImGui::Button("Browse###mon1"))
					{
					}

					ImGui::InputTextWithHint("Monster Type 2", "Monster Data File", &sMazeMonsters[1], ImGuiInputTextFlags_EnterReturnsTrue);
					ImGui::SameLine();
					if (ImGui::Button("Browse###mon2"))
					{
					}

					ImGui::InputTextWithHint("Decorations File", "Decorations Data File (doors, switches etc)", &sMazeDecorations, ImGuiInputTextFlags_EnterReturnsTrue);
					ImGui::SameLine();
					if (ImGui::Button("Browse###dec"))
					{
					}
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Monsters"))
				{
					if (ImGui::Button("Add Monster"))
					{

					}
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Items"))
				{
					if (ImGui::Button("Add Item"))
					{

					}
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Maze Simulation"))
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

	DoFileDialog_Open();
	DoFileDialog_Save();
}

void SmitED::CMazViewer::DrawMaze2D()
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

			if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
				PlaceWall(offset);

			if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
				PlaceDoor(offset);
			if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
				PlaceBlank(offset);

		}
	}

	draw_list->AddRectFilled(sp + ImVec2(0, 0), sp + ImVec2(32 * 15, 32 * 15), 0xf0343434);
	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			int offset = (y * 32) + x;

			uint8_t n, s, e, w;
			uint32_t colN, colS, colE, colW;
			colN = colE = colS = colW = 0x7f7f7f7f;

			n = 0b00000011 & (pMaz->walldata[offset][0]);
			e = 0b00000011 & (pMaz->walldata[offset][1]);
			s = 0b00000011 & (pMaz->walldata[offset][2]);
			w = 0b00000011 & (pMaz->walldata[offset][3]);
			int16_t drawDoor = 0x0000;
			if (n != 0 && e != 0 && s != 0 && w != 0)
			{
				ImVec2 st = ImVec2(float(x) * 15, float(y) * 15);
				ImVec2 ed = ImVec2(float(x + 1) * 15, float(y + 1) * 15);
				draw_list->AddRectFilled(sp + st, sp + ed, 0xFF7F7F7F);
			}
			else
			{
				if (n == 1)	colN = 0xFFFFFFFF;
				if (e == 1)	colE = 0xFFFFFFFF;
				if (s == 1)	colS = 0xFFFFFFFF;
				if (w == 1)	colW = 0xFFFFFFFF;

				if (n == 2)	colN = 0xFF7f7fFF;
				if (e == 2)	colE = 0xFF7f7fFF;
				if (s == 2)	colS = 0xFF7f7fFF;
				if (w == 2)	colW = 0xFF7f7fFF;

				if (n == 3) { colN = 0xFF7f7f7f; drawDoor += 0x01; }
				if (e == 3) { colE = 0xFF7f7f7f; drawDoor += 0x02; }
				if (s == 3) { colS = 0xFF7f7f7f; drawDoor += 0x04; }
				if (w == 3) { colW = 0xFF7f7f7f;  drawDoor += 0x08; }




				draw_list->AddLine(sp + ImVec2(float(x) * 15, float(y) * 15), sp + ImVec2((float(x) + 1) * 15, float(y) * 15), colN, 1);
				draw_list->AddLine(sp + ImVec2(float(x) * 15, float(y) * 15), sp + ImVec2((float(x) * 15), (1 + float(y)) * 15), colE, 1);
				draw_list->AddLine(sp + ImVec2(float(x) * 15, (1 + float(y)) * 15), sp + ImVec2(((1 + float(x)) * 15), (1 + float(y)) * 15), colS, 1);
				draw_list->AddLine(sp + ImVec2((1 + float(x)) * 15, float(y) * 15), sp + ImVec2(((1 + float(x)) * 15), (1 + float(y)) * 15), colW, 1);

				ImVec2 dl = ImVec2(4, -5);
				ImVec2 dr = ImVec2(-4, 5);

				if (drawDoor & 0x01)
					draw_list->AddRect(dl + sp + ImVec2(float(x) * 15, float(y) * 15), dr + sp + ImVec2((float(x) + 1) * 15, float(y) * 15), colN);
				if (drawDoor & 0x02)
					draw_list->AddRect(dr + sp + ImVec2(float(x) * 15, float(y) * 15), dl + sp + ImVec2((float(x) * 15), (1 + float(y)) * 15), colE);
				if (drawDoor & 0x04)
					draw_list->AddRect(dl + sp + ImVec2(float(x) * 15, (1 + float(y)) * 15), dr + sp + ImVec2(((1 + float(x)) * 15), (1 + float(y)) * 15), colS);
				if (drawDoor & 0x08)
					draw_list->AddRect(dr + sp + ImVec2((1 + float(x)) * 15, float(y) * 15), dl + sp + ImVec2(((1 + float(x)) * 15), (1 + float(y)) * 15), colW);

				//auto p = pCPS->_pal._data[pCPS->_bitmap->pData[float(y) * 320 + float(x)]];
				//U32 col = p.r << 24 | p.g << 16 | p.b << 8 | 0x0F;
				//draw_list->AddRectFilled(sp + st, sp + ed, col);
				//draw_list->AddLine(sp, sp+ImVec2(20,30), col);
			}
		}
	}
	std::string subInfo = "";
	subInfo.append(std::to_string(mapX)).append(" ").append(std::to_string(mapY));
	ImGui::Text(subInfo.c_str());
	//ImGui::Dummy(ImVec2(65*15, 32*15));

}


void SmitED::CMazViewer::PlaceBlank(int offset)
{
	
	pMaz->walldata[offset][0] = 0x00;
	pMaz->walldata[offset][1] = 0x00;
	pMaz->walldata[offset][2] = 0x00;
	pMaz->walldata[offset][3] = 0x00;
	
}


void SmitED::CMazViewer::PlaceDoor(int offset)
{
	pMaz->walldata[offset][0] = 0x03;
	pMaz->walldata[offset][1] = 0x03;
	pMaz->walldata[offset][2] = 0x03;
	pMaz->walldata[offset][3] = 0x03;	
}

void SmitED::CMazViewer::PlaceWall(int offset)
{
	if (offset % 2)
	{
		pMaz->walldata[offset][0] = 0x01;
		pMaz->walldata[offset][1] = 0x02;
		pMaz->walldata[offset][2] = 0x01;
		pMaz->walldata[offset][3] = 0x02;
	}
	else
	{
		pMaz->walldata[offset][0] = 0x02;
		pMaz->walldata[offset][1] = 0x01;
		pMaz->walldata[offset][2] = 0x02;
		pMaz->walldata[offset][3] = 0x01;
	}
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
				std::vector<CScriptRoutine::sError > vecErrors;
				m_pScriptCompiler->Compile(textToSave, vecErrors);
				TextEditor::ErrorMarkers aMarkers;
				if (!vecErrors.empty())
				{
					// we had errors
					for (auto error : vecErrors)
					{
						aMarkers.emplace(error.line, error.sErrorString);
					}
				
				}
				pTextEditor->SetErrorMarkers(aMarkers);

			}
			std::vector<std::string> filters = { "Maze Data File", "*.maz" };
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

inline void SmitED::CMazViewer::DoFileDialog_Open()
{
	if (open_file && open_file->ready())
	{
		auto result = open_file->result();
		if (!result.empty())
		{
			//ns::debug::write_line("Opened File %s", result[0].c_str());
			std::ifstream ifsFile(result[0].c_str(), std::ios_base::binary);
			if (!ifsFile.fail())
			{
				LoadMazeFile(ifsFile);
			}
			ifsFile.close();
		}
		//std::cout << "Opened file " << result[0] << "\n";
		open_file = nullptr;
	}
}

inline void SmitED::CMazViewer::DoFileDialog_Save()
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
			WriteMazeFile(ofsFile);
			ofsFile.close();
		}
		//std::cout << "Opened file " << result[0] << "\n";
		save_file = nullptr;
	}
}

inline const TextEditor::LanguageDefinition& SmitED::CMazViewer::LangSmyte()
{
	static bool inited = false;
	static TextEditor::LanguageDefinition langDef;
	if (!inited)
	{
		static const char* const keywords[] = {
			"If" ,"Gosub" ,"Return" ,"End" ,"Goto", "ClearFlag" ,"SetFlag", "PartyVisible", "RollDice", "HasClass", "HasRace", "TriggerFlag", "PointerItem", "WallSide", "PartyDirection", "ElseGoto", "LevelFlag", "GlobalFlag", "PartyOnPos", "MonstersOnPos", "ItemsOnPos", "WallNumber", "Or", "And", "Greaterthan", "Lessthan", "Notequal", "Equal" };

		for (auto& k : keywords)
			langDef.mKeywords.insert(k);

		 static const char* const identifiers[] = {
			"Encounter" ,"IdentifyItems" ,"Turn" ,"Launcher" ,"AddItem" ,"GiveXp" ,"ChangeLevel" ,"RemoveItem" ,"Damage" ,"Sound" ,"Message" ,"StealItem" ,"Teleport" ,"AddMonster" ,"CloseDoor" ,"OpenDoor" ,"ChangeWall" ,"SetWall"
		 };
		 for (auto& k : identifiers)
		 {
		 	TextEditor::Identifier id;
		 	id.mDeclaration = "Built-in function";
		 	langDef.mIdentifiers.insert(std::make_pair(std::string(k), id));
		 }

		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", TextEditor::PaletteIndex::String));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\\'[^\\\']*\\\'", TextEditor::PaletteIndex::String));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", TextEditor::PaletteIndex::Number));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", TextEditor::PaletteIndex::Number));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[+-]?[0-9]+[Uu]?[lL]?[lL]?", TextEditor::PaletteIndex::Number));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", TextEditor::PaletteIndex::Punctuation));

		langDef.mCommentStart = "/*";
		langDef.mCommentEnd = "*/";
		langDef.mSingleLineComment = "//";

		langDef.mCaseSensitive = true;
		langDef.mAutoIndentation = false;

		langDef.mName = "Symte Script";

		inited = true;
	}
	return langDef;
}


void SmitED::CMazViewer::OnDataSet()
{
	// load in a maze and decrypt the script.

}

