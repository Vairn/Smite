#pragma once

#include "CHexViewer.h"
#include <imgui.h>
#include "imgui_memory_editor.h"
#include "misc/cpp/imgui_stdlib.h"
#include "TextEditor.h"

#include "portable-file-dialogs.h"
#include "../../libSmite/typeDefs.h"

#include <vector>

//   event trigger points
//
//   XX,YY   coordinates
//   MASK    mask
//           $08 = on enter
//           $10 = on leave
//           $20 = on put item
//           $40 = on get item
//           $80 = on throw item


struct sMaze;
class CScriptRoutine;
#define MKTAG(a0,a1,a2,a3) ((uint32_t)((a3) | ((a2) << 8) | ((a1) << 16) | ((a0) << 24)))
#define MKTAG16(a0,a1) ((uint16_t)((a1) | ((a0) << 8)))

namespace SmitED
{
	struct sCommand
	{
		sCommand(std::string _sName, int _params) { sName = _sName; paramCount = _params; };
		std::string sName;
		int paramCount;
	};

	class CMazViewer : public SmitED::CHexViewer
	{
	public:
		CMazViewer();
		void update() override;
		void DrawMaze2D();
		virtual void OnDataSet(void);
		
	private:
		void PlaceBlank(int offset);
		void PlaceDoor(int offset);
		void PlaceWall(int offset);
		void DrawMenuBar();
		void DoFileDialog_Open();

		void DoFileDialog_Save();

		const TextEditor::LanguageDefinition& LangSmyte();

		void LoadMazeFile(std::ifstream& ifsFile);
	protected:
	
	private:
		sMaze *pMaz;
		TextEditor* pTextEditor;
		std::shared_ptr<pfd::open_file> open_file;
		std::shared_ptr<pfd::save_file> save_file;
		std::vector < std::pair<uint8_t, sCommand>> vecCommands;
		

		static CScriptRoutine* m_pScriptCompiler;
		std::string sMazeMonsters[2];
		std::string sMazeWallset;
		std::string sMazeDecorations;
		static int instance;
		void WriteMazeFile(std::ofstream& ofsFile);
	};
}