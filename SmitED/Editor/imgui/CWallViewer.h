#pragma once
#include "CHexViewer.h"
#include <imgui.h>
#include "imgui_memory_editor.h"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <vector>
#include <map>
#include <memory>
#include <cstdint>
struct FIBITMAP;

namespace pt = boost::property_tree;

#include "portable-file-dialogs.h"
namespace SmitED
{
	struct sWallSetTile
	{
		std::string sName;
		std::string type;

		int8_t location[2];
		int16_t screen[2];
		int16_t coords[4];
		FIBITMAP* pFrame = nullptr;
		bool flip = false;
	};
	class CWallViewer : public SmitED::CHexViewer
	{
	public:
		CWallViewer();
		void update() override;

		void RenderBackground(FIBITMAP* pDst);

		virtual void OnDataSet(void);
	protected:
		bool ImportJson(const char* sFilename);

		void ReadTileInfo(SmitED::sWallSetTile* pTileInfo, const std::pair<std::string, pt::ptree>& tile);

	private:
		FIBITMAP* pSrcImage;
		FIBITMAP* pScreenImage;
		FIBITMAP* pBackgroundImage;
		pt::ptree m_wallsetJson;
		std::shared_ptr<pfd::open_file> open_file;
		std::shared_ptr<pfd::save_file> save_file;


		int windowWidth = 240;
		int windowHeight = 180;
		int width,depth;

		std::map<int, std::vector<sWallSetTile*>> m_wallSetTiles;
		void SaveTileset(std::string& result);
		uint8_t GetTypeIndex(std::string& typeStr);
	};

}