#pragma once

#include "CHexViewer.h"
#include <imgui.h>
#include "imgui_memory_editor.h"
#include "portable-file-dialogs.h"
#include "../../libSmite/typeDefs.h"
#include "../../libSmite/BlitzShape.h"
namespace SmitED
{
	class CMonsterEditor: public SmitED::CHexViewer
	{
	public:
		CMonsterEditor();
		void update() override;

		

		virtual void OnDataSet(void);
	protected:

		void DoFileDialog_Open();

		void DoFileDialog_Save();
	private:

		std::shared_ptr<pfd::open_file> open_file;
		std::shared_ptr<pfd::save_file> save_file;
		sBlitzShapes* m_pShapes;
		int32_t m_uiCurrentID;
		color_palette palette;
	};

}