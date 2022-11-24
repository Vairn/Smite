#include "CWallViewer.h"
#include <imgui.h>
#include <FreeImage.h>
//#include "portable-file-dialogs.h"

#include <fstream>
#include <filesystem>
#include <minmax.h>
#include "../../libSmite/typeDefs.h"

const int8_t STANDARD_PALETTE[] = { 00,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255 };
const int8_t STANDARD_COLOR_SIZE = 16;
const uint8_t STANDARD_PALETTE_VAL_DIF = 17;
int16_t dwColorMapTable[16*16*16];

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include <algorithm>
#include "../../libSmite/common.h"
static int32_t iPosition = ((1 & 0x1f) * 32) + (1 & 0x1F);;
static int8_t iFacing = 0;

std::string str_tolower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return std::tolower(c); } // correct
	);
	return s;
}

void createPaletteTable()
{
	int  nColorMapIdx = 0;
	for (int nBlueIdx = 0; nBlueIdx < STANDARD_COLOR_SIZE; ++nBlueIdx)
	{
		for (int nGreenIdx = 0; nGreenIdx < STANDARD_COLOR_SIZE; ++nGreenIdx)
		{
			for (int nRedIdx = 0; nRedIdx < STANDARD_COLOR_SIZE; ++nRedIdx)
			{
				RGBQUAD objColor;
				objColor.rgbRed = STANDARD_PALETTE[nRedIdx];
				objColor.rgbGreen = STANDARD_PALETTE[nGreenIdx];
				objColor.rgbBlue = STANDARD_PALETTE[nBlueIdx];
				objColor.rgbReserved = 0;
				memcpy(&dwColorMapTable[nColorMapIdx], &objColor, sizeof(RGBQUAD));
				++nColorMapIdx;
			}
		}
	}
}

uint8_t GetPixelValue(uint32_t uPixelValue_i)
{
	uint8_t uRetValue = 0;
	uint8_t uPos = uPixelValue_i / STANDARD_PALETTE_VAL_DIF;
	if (0 == uPixelValue_i % STANDARD_PALETTE_VAL_DIF)
	{
		uRetValue = uPixelValue_i / STANDARD_PALETTE_VAL_DIF;
	}
	else
	{
		if (abs((int)uPixelValue_i - STANDARD_PALETTE[uPos]) >
			abs((int)uPixelValue_i - STANDARD_PALETTE[uPos + 1]))
		{
			uRetValue = uPos + 1;
		}
		else
		{
			uRetValue = uPos;
		}
	}
	return uRetValue;
}

bool sortWallset(SmitED::sWallSetTile* first, SmitED::sWallSetTile* second)
{
	if (second->location[1] > first->location[1])
		return true;

	if (second->location[1] == first->location[1])
	{
		if (second->type.compare("front") == 0 && first->type.compare("side") == 0)
		{
			return true;
		}

		if (second->type.compare("side") == 0 && first->type.compare("front") == 0)
		{
			return false;
		}

		return (second->location[0] < first->location[0]);
	}
	return 0;
}
typedef struct _sMazeDir
{
	int8_t xs, ys;
}sMazeDir;

typedef struct _sMazePos
{
	int8_t xDelta, yDelta, facing;
}sMazePos;


static sMazePos CMazePos[26] = {
	{ -3, -3, 1},
	{ -2, -3, 1},
	{ -1, -3, 1},

	{  1, -3, 3},
	{  2, -3, 3},
	{  3, -3, 3},

	{ -2, -3, 2},
	{ -1, -3, 2},
	{  2, -3, 2},
	{  1, -3, 2},
	{  0, -3, 2},

	{ -2, -2, 1},
	{ -1, -2, 1},

	{  1, -2, 3},
	{  2, -2, 3},

	{ -1, -2, 2},
	{  1, -2, 2},
	{  0, -2, 2},

	{ -1, -1, 1},

	{  1, -1, 3},

	{ -1, -1, 2},
	{  1, -1, 2},
	{  0, -1, 2},

	{ -1,  0, 1},

	{  1,  0, 3},

	{  0,  0, 2},
};

static sMazeDir CMazeDr[4] = {
	{1,  1},  // north
	{ -1, 1},  // east
	{ -1, -1},  // south
	{1, -1},  // west
};

int32_t mazeMove(int32_t pos, int32_t dir)
{
	int x, y;
	x = pos % 32;
	y = div(int(pos), 32).quot;
	switch (dir)
	{
	case 0: y--;
		break;
	case 1:	x++;
		break;

	case 2:	y++;
		break;

	case 3:	x--;
		break;
	}
	// is this square blocking?
	long newPos = ((y & 0x1f) * 32) + (x & 0x1F);

	//for(int i=0;i<26;i++)
	int wmi = mazeData[y][x];
	if (wmi == 1)
		return pos;
	//t wmi = m_pMazeInfo->_mazeCells[((y & 0x1F) * 32) + (x & 0x1F)].wall[dir];

	//if (wmi <= 24)
	//{
	//	if (CWALLDATA[wmi].flags & WALLFLAG_PASSPARTY)
	//		return newPos;
	//}
	///*else if (checkDecorationCollision(translateWMI(wmi)) == false)
	//{
	//	return newPos;
	//}*/
	return newPos;
}
SmitED::CWallViewer::CWallViewer()
{
	//currentShape = 0;
	//createPaletteTable();
	m_uiCurrentTypeID = 0;
	m_uiCurrentTileID = 0;
}

SmitED::CWallViewer::~CWallViewer()
{
	printf("Death Becomes Me");
}

void SmitED::CWallViewer::update()
{
	
	static int iWall = 0;
	 
	begin();
	
	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Graphics"))
		{
		


			ImGuiIO& io = ImGui::GetIO();
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			if (m_wallSetTiles.empty() == false)
			{
				
				ImGui::SliderInt("Current Item Type", &m_uiCurrentTypeID, 0, m_wallSetTiles.size()-1);
				auto currentSet = m_wallSetTiles[m_uiCurrentTypeID];
				if (currentSet.size() > 0)
				{

					if (m_uiCurrentTileID >= currentSet.size())
					{
						m_uiCurrentTileID = 0;
					}
					ImGui::SliderInt("Tile", &m_uiCurrentTileID, 0, currentSet.size()-1);
					ImVec2 sp = ImGui::GetCursorScreenPos();
					auto tile = m_wallSetTiles[m_uiCurrentTypeID][m_uiCurrentTileID];
		
					ImVec2 canvas_sz = ImVec2(windowWidth * 3, windowHeight * 3);
					ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
					for (auto y = 0; y < tile->coords[3]; y++)
					{
						for (auto x = 0; x < tile->coords[2]; x++)
						{
							//auto index = sprite->chunkyBuffer[(y * width) + x];

							RGBQUAD rgb;
							FreeImage_GetPixelColor(tile->pFrame, x, y, &rgb); 
							ImU32 col = ImGui::GetColorU32(IM_COL32(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue, 255));

							int sx = tile->screen[0] + x;
							int sy = tile->screen[1] + y;
							auto st = ImVec2((sx * 3), sy * 3);
							auto ed = ImVec2((sx + 1) * 3, (sy + 1) * 3);
							if(st.x < 240*3)
								draw_list->AddRectFilled(sp + st, sp + ed, col);
						}
					}
					ImGui::InputScalar("Screen X:", ImGuiDataType_S16, &tile->screen[0]);
					ImGui::SameLine();
					ImGui::InputScalar("Screen Y:", ImGuiDataType_S16,&tile->screen[1]);
					
					ImGui::InputScalar("Width:", ImGuiDataType_S16, &tile->coords[2]);
					ImGui::SameLine(); 
					ImGui::InputScalar("Height:", ImGuiDataType_S16, &tile->coords[3]);

					ImGui::InputScalar("Location X:", ImGuiDataType_S8, &tile->location[0]);
					ImGui::SameLine();
					ImGui::InputScalar("Location Y:", ImGuiDataType_S8, &tile->location[1]);



				}
				else
				{
					std::string text = "No Tiles in Set";
					ShowPlaceholder(text);
				}
			}
			else
			{
				std::string text = "Import in a Wallset to edit.";
				ShowPlaceholder(text);

			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Palette"))
		{
			
			ImGui::EndTabItem();

		}
		if (ImGui::BeginTabItem("Maze Simulation"))
		{
			DrawMazeView();

			DrawMazeControls();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("HexView"))
		{
			const ImVec2 sp = ImGui::GetCursorScreenPos();

			memEdit->DrawContents(pData, uiDataSize);
			ImGui::EndTabItem();
			//ImGui::SetCursorScreenPos(sp);
		}
		ImGui::SameLine(0);
		if (ImGui::Button("Import"))
		{
			std::vector<std::string> filters = { "JSON Wall Mapping", "*.json *.jsn" };
			open_file = std::make_shared<pfd::open_file>("Choose file", "C:\\", filters);

		}
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			std::vector<std::string> filters = { "Wall Mapping", "*.wll" };
			save_file = std::make_shared<pfd::save_file>("Save file As", "C:\\", filters);
		}

		ImGui::EndTabBar(); 

	}

	end();

	if (open_file)
	{
		if (open_file->ready())
		{
			auto result = open_file->result();
			if (result.size() != 0)
			{
				pfd::notify("Loading Wallset", "Loading Json Data and Generating wallset");
				//SetWorkingDirectory();
				ImportJson(result[0].c_str());
			}

			open_file = nullptr;
		}
	}

	if (save_file)
	{
		if (save_file->ready())
		{
			auto result = save_file->result();
			if (result.size() != 0)
			{
				SaveTileset(result);
			}
			save_file = nullptr;
		}
	}
}

void SmitED::CWallViewer::DrawMazeControls()
{
	{
		int x = 0, y = 0;

		x += (iPosition % 32);
		y += iPosition / 32;//div(int(position), 32).quot;
		ImGui::SliderInt("X###1", &x, 0, 31);

		ImGui::SliderInt("Y###2", &y, 0, 31);
		//iPosition = ((y & 0x1f) * 32) + (x & 0x1F);
		iPosition = ((y & 0x1F) * 32) + (x & 0x1F);
	}
	ImGui::SliderInt("facing", (int*)&iFacing, 0, 3);
	if (ImGui::Button("TL", ImVec2(30, 30)))
	{
		iFacing--;
		if (iFacing < 0)
			iFacing = 3;
		FreeImage_FlipHorizontal(pBackgroundImage);
	}
	ImGui::SameLine();
	if (ImGui::Button("/\\", ImVec2(30, 30)))
	{

		iPosition = mazeMove(iPosition, (iFacing) % 4);
		FreeImage_FlipHorizontal(pBackgroundImage);
	}
	ImGui::SameLine();
	if (ImGui::Button("TR", ImVec2(30, 30)))
	{

		iFacing++;
		if (iFacing > 3)
			iFacing = 0;
		FreeImage_FlipHorizontal(pBackgroundImage);
	}

	if (ImGui::Button("<", ImVec2(30, 30)))
	{
		iPosition = mazeMove(iPosition, (iFacing + 3) % 4);
		FreeImage_FlipHorizontal(pBackgroundImage);

	}
	ImGui::SameLine();
	if (ImGui::Button("V", ImVec2(30, 30)))
	{
		iPosition = mazeMove(iPosition, (iFacing + 2) % 4);
		FreeImage_FlipHorizontal(pBackgroundImage);
	}

	ImGui::SameLine();
	if (ImGui::Button(">", ImVec2(30, 30)))
	{
		iPosition = mazeMove(iPosition, (iFacing + 1) % 4);
		FreeImage_FlipHorizontal(pBackgroundImage);
	}
}

void SmitED::CWallViewer::DrawMazeView()
{
	if (!m_wallSetTiles.empty())
	{
		FreeImage_Paste(pScreenImage, pBackgroundImage, 0, 0, 255);

		//RenderBackground(pScreenImage);
		/*for (int y = 0; y < 176; y++)
		{
			for (int x = 0; x < 240; x++)
			{
				RGBQUAD rgb;
				rgb.rgbRed = 32;
				rgb.rgbBlue= 32;
				rgb.rgbGreen= 32;
				FreeImage_SetPixelColor(pScreenImage, x, y, &rgb);
			}
		}*/
		//FreeImage_ ( pScreenImage
		// Draw the Fake Level!
		// Do Floor and Roofie

		int x = 0, y = 0, dr = 0, wmi = 0;

		for (int i = 0; i < 26; i++)
		{
			if ((iFacing % 2) != 0)
			{
				x = CMazeDr[iFacing].xs * CMazePos[i].yDelta;
				y = CMazeDr[iFacing].ys * CMazePos[i].xDelta;
			}
			else
			{
				x = CMazeDr[iFacing].xs * CMazePos[i].xDelta;
				y = CMazeDr[iFacing].ys * CMazePos[i].yDelta;
			}

			//x += (iPosition % 32);
			//y += div(int(iPosition), 32).quot;
			dr = ((iFacing + CMazePos[i].facing) & 0x03);
			//wmi = m_pMazeInfo->_mazeCells[((y & 0x1F) * 32) + (x & 0x1F)].wall[dr];
			//if (x<0 || y<0)
			//	continue;
			int wmi = mazeData[y + div(int(iPosition), 32).quot][x + (iPosition % 32)];
			if (wmi == 0)
				continue;
			printf("x:%i y:%i - %i\n", x, y, wmi);
			// floor;
			//RenderBackground();
			//continue;
			for (const auto& tilesets : m_wallSetTiles)
			{
				for (const auto tile : tilesets.second)
				{
					auto idx = GetTypeIndex(tile->sName);
					if (idx != 0 && wmi == idx)
					{

						int tx = tile->location[0];// *CMazeDr[iFacing].xs;
						int ty = tile->location[1];// *CMazeDr[iFacing].ys;
						//if ((iFacing % 2) != 0)
						//{
						//	tx *= -1;// CMazeDr[iFacing].ys;
							// ty *= -1;//CMazeDr[iFacing].xs;
						//}
						//else
						//{
							//ty *= -1;// CMazeDr[iFacing].ys;
						//}
						if (tx == CMazePos[i].xDelta && ty == CMazePos[i].yDelta)
						{
							// printf("%d, %d\n", tx, ty);
							//FreeImage_Paste(pScreenImage, tile->pFrame, tile->screen[0], tile->screen[1],254);
							for (int16_t py = 0; py < tile->coords[3]; py++)
							{
								for (int16_t px = 0; px < tile->coords[2]; px++)
								{
									RGBQUAD rgb;
									FreeImage_GetPixelColor(tile->pFrame, px, py, &rgb);
									if (rgb.rgbRed == 252 && rgb.rgbGreen == 254 && rgb.rgbBlue == 252) continue;
									FreeImage_SetPixelColor(pScreenImage, tile->screen[0] + px, tile->screen[1] + py, &rgb);
								}
							}
						}
						//tx *= -1;
						////if (tx == x && ty == y)
						//{
						//	FreeImage_FlipHorizontal(tile->pFrame);
						//	//FreeImage_Paste(pScreenImage, tile->pFrame, tile->screen[0], tile->screen[1],254);
						//	for (int16_t py = 0; py < tile->coords[3]; py++)
						//	{
						//		for (int16_t px = 0; px < tile->coords[2]; px++)
						//		{
						//			RGBQUAD rgb;
						//			FreeImage_GetPixelColor(tile->pFrame, px, py, &rgb);
						//			if (rgb.rgbRed == 4 && rgb.rgbGreen == 58 && rgb.rgbBlue == 132) continue;
						//			FreeImage_SetPixelColor(pScreenImage, (240-tile->coords[2] - tile->screen[0]) + px, tile->screen[1] + py, &rgb);
						//		}
						//	}
						//	FreeImage_FlipHorizontal(tile->pFrame);
						//}
					}
				}
			}
			//DrawWall(wmi, i);
		}
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		const ImVec2 sp = ImGui::GetCursorScreenPos();
		for (int y = 0; y < windowHeight; y++)
		{
			for (int x = 0; x < windowWidth; x++)
			{
				//auto p = pCPS->_pal._data[pCPS->_bitmap->pData[y * 320 + x]];
				//U32 col = p.r << 24 | p.g << 16 | p.b << 8 | 0x0F;
				RGBQUAD p;
				FreeImage_GetPixelColor(pScreenImage, x, y, &p);

				ImU32 col = ImGui::GetColorU32(IM_COL32(p.rgbRed, p.rgbGreen, p.rgbBlue, 255));

				auto st = ImVec2((x * 3), y * 3);
				auto ed = ImVec2((x + 1) * 3, (y + 1) * 3);
				draw_list->AddRectFilled(sp + st, sp + ed, col);
				//draw_list->AddLine(sp, sp+ImVec2(20,30), col);
			}
		}

		ImGui::Dummy(ImVec2(windowWidth * 3, windowHeight * 3));
		//ImGui::PopItemWidth();
		//Sleep(20);
		// iFacing++;
		//iFacing  = iFacing % 4;


	}
}

void SmitED::CWallViewer::RenderBackground(FIBITMAP* pDst)
{
	for (const auto& tilesets : m_wallSetTiles)
	{
		for (const auto tile : tilesets.second)
		{
			auto idx = GetTypeIndex(tile->sName);
			if (idx == 0)
			//if (tlx == x && tly == y)
			{
				//FreeImage_Paste(pScreenImage, tile->pFrame, tile->screen[0], tile->screen[1],254);
				for (int16_t py = 0; py < tile->coords[3]; py++)
				{
					for (int16_t px = 0; px < tile->coords[2]; px++)
					{
						RGBQUAD rgb;
						FreeImage_GetPixelColor(tile->pFrame, px, py, &rgb);
						// if (rgb.rgbRed == 0 && rgb.rgbGreen == 0 && rgb.rgbBlue == 0) continue;
						if (rgb.rgbRed == 252 && rgb.rgbGreen == 254 && rgb.rgbBlue == 252) continue;
						//if (rgb.rgbRed == 12 && rgb.rgbGreen == 34 && rgb.rgbBlue == 36) continue;
						FreeImage_SetPixelColor(pDst, tile->screen[0] + px, tile->screen[1] + py, &rgb);
					}
				}
			}
		}
	}
	/*
	// ceiling;
	for (const auto& tile : m_wallSetTiles[1])
	{
		for (int16_t py = 0; py < tile->coords[3]; py++)
		{
			for (int16_t px = 0; px < tile->coords[2]; px++)
			{
				RGBQUAD rgb;


				FreeImage_GetPixelColor(tile->pFrame, px, py, &rgb);
				if (rgb.rgbRed == 12 && rgb.rgbGreen == 34 && rgb.rgbBlue == 36) continue;
				FreeImage_SetPixelColor(pDst, tile->screen[0] + px, tile->screen[1] + py, &rgb);
			}
		}
	}
	*/
}

bool SmitED::CWallViewer::ImportJson(const char* sFilename)
{
	
	std::ifstream is(sFilename);
	
	pt::read_json(sFilename, m_wallsetJson);
	std::filesystem::path sImageName = sFilename;
	sImageName.replace_extension(".png");

	pSrcImage = FreeImage_Load(FIF_PNG,sImageName.string().c_str(), 0);
	FreeImage_SetTransparentIndex(pSrcImage, 2);
	std::filesystem::path sFolder = sFilename;
	sFolder.replace_extension("");
	std::filesystem::create_directory(sFolder);
	std::string version;
	version = m_wallsetJson.get("version", "0.0.0");
	importVersion = 1;
	if (version.compare("0.0.1") == 0)
	{
		importVersion = 0;
	}
	
	windowWidth = m_wallsetJson.get("resolution.width",0);
	windowHeight = m_wallsetJson.get("resolution.height",0);
	width = m_wallsetJson.get("width", 0);
	depth = m_wallsetJson.get("depth", 0);
	pScreenImage = FreeImage_Allocate(windowWidth, windowHeight,32);
	auto layers = m_wallsetJson.get_child("layers");
	//

	//printf("%x,%x - %x, %x, %x\n", windowWidth, windowHeight, width, depth, layers);
	for (const auto& layer : layers)
	{
		int id = layer.second.get("id", -1);
		if (id == -1)
			continue;
		//printf("%s\n", layer.second.get<std::string>("name",""));
		auto tiles = layer.second.get_child("tiles");
		int index = 0;
		std::string sName = layer.second.get<std::string>("name", "");

		for (const auto& tile : tiles)
		{
			auto pTileInfo = new sWallSetTile();
			ReadTileInfo(pTileInfo, tile);
			pTileInfo->sName = sName;
			m_wallSetTiles[id].emplace_back(pTileInfo);
			pTileInfo->pFrame = FreeImage_Copy(pSrcImage, pTileInfo->coords[0], pTileInfo->coords[1], pTileInfo->coords[0]+pTileInfo->coords[2], pTileInfo->coords[1]+pTileInfo->coords[3]);
			index++;

			//if (pTileInfo->location[0] > 0 && pTileInfo->type.compare("side") == 0)
			if (importVersion == 0)
			{
				// website exporter says to flip it.
				if (pTileInfo->flip)
				{
					pTileInfo->screen[0] -= pTileInfo->coords[2];
					pTileInfo->pFrame = FreeImage_Copy(pSrcImage, pTileInfo->coords[0], pTileInfo->coords[1], pTileInfo->coords[0] + pTileInfo->coords[2], pTileInfo->coords[1] + pTileInfo->coords[3]);
					FreeImage_FlipHorizontal(pTileInfo->pFrame);
					pTileInfo->flip = true;
				}

				// Website version doesn't declare the front facing wall-set for anything other than 0.
				if (pTileInfo->type.compare("front") == 0)
				{
					for (int x = -width; x < width; x++)
					{
						if (x == 0)
							continue;

						auto pTileInfo = new sWallSetTile();
						ReadTileInfo(pTileInfo, tile);
						pTileInfo->sName = sName;
						pTileInfo->location[0] = x;
						pTileInfo->screen[0] += (x * pTileInfo->fullwidth);
						if (pTileInfo->screen[0] < 0 && (pTileInfo->screen[0] + pTileInfo->coords[2]) > 0)
						{
							pTileInfo->coords[2] += pTileInfo->screen[0];
							pTileInfo->coords[0] += -pTileInfo->screen[0];
							pTileInfo->screen[0] = 0;
						}
						if (pTileInfo->screen[0] + pTileInfo->coords[2] > 240)
						{
							auto newWidth = 240 - pTileInfo->screen[0] ;
							

							pTileInfo->coords[2] = newWidth;
						}
						if (pTileInfo->screen[0]>= 0 && pTileInfo->screen[0] <240)
						{
						//if (pTileInfo->screen[0]>)
							m_wallSetTiles[id].emplace_back(pTileInfo);
							pTileInfo->pFrame = FreeImage_Copy(pSrcImage, pTileInfo->coords[0], pTileInfo->coords[1], pTileInfo->coords[0] + pTileInfo->coords[2], pTileInfo->coords[1] + pTileInfo->coords[3]);
						}
						//pTileInfo->pFrame = FreeImage_ConvertTo32Bits(pTileInfo->pFrame);
						//FreeImage_SetPalette()
						//FreeImage_FlipHorizontal(pTileInfo->pFrame);
						//pTileInfo->flip = true;
					}
				}
			}
			else
			{
				if (pTileInfo->location[0] > 0 && pTileInfo->type.compare("side") == 0)
				{
					auto pTileInfo = new sWallSetTile();
					ReadTileInfo(pTileInfo, tile);
					pTileInfo->sName = sName;
					pTileInfo->location[0] *= -1;
					pTileInfo->screen[0] = windowWidth - pTileInfo->coords[2] - pTileInfo->screen[0];
					m_wallSetTiles[id].emplace_back(pTileInfo);
					pTileInfo->pFrame = FreeImage_Copy(pSrcImage, pTileInfo->coords[0], pTileInfo->coords[1], pTileInfo->coords[0] + pTileInfo->coords[2], pTileInfo->coords[1] + pTileInfo->coords[3]);
					//pTileInfo->pFrame = FreeImage_ConvertTo32Bits(pTileInfo->pFrame);
					//FreeImage_SetPalette()
					FreeImage_FlipHorizontal(pTileInfo->pFrame);
					pTileInfo->flip = true;
					//index++;
				}
			}
			
			
		}
	}

	for (auto &set:m_wallSetTiles)
	{
		auto itb = set.second.begin();
		auto ite = set.second.end();
		std::sort(itb,ite,sortWallset);
		int index = 0;
		//itb = set.second.begin();
		//ite = set.second.end();
		//std::reverse(itb, ite);
		for (auto& tile : set.second)
		{
			std::string saveFilename = sFolder.generic_string();
			saveFilename.append("\\");
			saveFilename.append(tile->sName);
			saveFilename.append("_");
			saveFilename.append(tile->type);
			saveFilename.append("_");
			saveFilename.append(std::to_string(index)).append(".png");
			FreeImage_Save(FIF_PNG, tile->pFrame, saveFilename.c_str());
			//FreeImage_SetTransparentIndex(pTileInfo->pFrame, 2);
			tile->pFrame = FreeImage_ConvertTo32Bits(tile->pFrame);
			FreeImage_FlipVertical(tile->pFrame);
			index++;
		}
	}

	pBackgroundImage = FreeImage_Allocate(windowWidth, windowHeight, 32);
	RenderBackground(pBackgroundImage);
	WindowName(sFolder.generic_string());
	FreeImage_FlipVertical(pSrcImage);
	return false;

}

void SmitED::CWallViewer::ReadTileInfo(SmitED::sWallSetTile* pTileInfo, const std::pair<std::string, pt::ptree>& tile)
{
	pTileInfo->type = tile.second.get("type", "");

	if (importVersion == 0)
	{
		pTileInfo->location[0] = tile.second.get("tile.x", 0);
		//pTileInfo->location[0] *= -1;
		pTileInfo->location[1] = tile.second.get("tile.z", 0);
	}
	else
	{
		pTileInfo->location[0] = tile.second.get("tile.x", 0);
		
		pTileInfo->location[1] = tile.second.get("tile.y", 0);
	}
	pTileInfo->screen[0] = tile.second.get("screen.x", 0);
	pTileInfo->screen[1] = tile.second.get("screen.y", 0);

	pTileInfo->coords[0] = tile.second.get("coords.x", 0);
	pTileInfo->coords[1] = tile.second.get("coords.y", 0);
	pTileInfo->coords[2] = tile.second.get("coords.w", 0);
	pTileInfo->coords[3] = tile.second.get("coords.h", 0);
	pTileInfo->flip = tile.second.get("flipped", false);
	pTileInfo->fullwidth = tile.second.get("coords.fullWidth", 0);
}

void SmitED::CWallViewer::SaveTileset(std::string& result)
{
	uint8_t cCount = 64;// FreeImage_GetColorsUsed(pSrcImage);
	std::ofstream fout(result, std::ios_base::binary);
	fout << "WLL";
	fout << (uint8_t)cCount;
	bool bSwapped = false;
	auto palette = FreeImage_GetPalette(pSrcImage);
	for (BYTE c = 0; c < cCount; c++)
	{
		// are we the transparent colour.
		if (palette[c].rgbRed == 252 && palette[c].rgbGreen == 254 && palette[c].rgbBlue == 252)
		{
			BYTE zero = 0;
			//FreeImage_SwapColors(pSrcImage, &palette[c], &palette[0], false);
			FreeImage_SwapPaletteIndices(pSrcImage, &c, &zero);
			palette[c].rgbRed = 0; palette[c].rgbGreen = 0; palette[c].rgbBlue = 0;
		}

	}
	 //palette = FreeImage_GetPalette(pSrcImage);
	for (int c = 0; c < cCount; c++)
	{
		fout << int8_t(ceil(palette[c].rgbRed ));
		fout << int8_t(ceil(palette[c].rgbGreen ));
		fout << int8_t(ceil(palette[c].rgbBlue));
	}

	// fout = WriteBackground(fout);

	uint16_t tilecount = 0;

	for (const auto& tileItr:m_wallSetTiles)
	{
		for (const auto&tile:tileItr.second)
		{
			auto idx = GetTypeIndex(tile->sName);
			// ignore floors and ceilings
			if (idx != 0)
				tilecount++;
		}
	}
	int8_t t01 = tilecount;
	int8_t t02 = (tilecount >> 8) & 0xFF;
	fout << t02 << t01;

	fout << (uint8_t)m_wallSetTiles.size();
	for (const auto &tileItr:m_wallSetTiles)
	{
		fout << (uint8_t)tileItr.second.size();
		for (auto tile : tileItr.second)
		{
			fout << GetTypeIndex(tile->sName);
			fout << (int8_t)tile->location[0];
			fout << (int8_t)tile->location[1];
			int8_t s01 = tile->screen[0];
			int8_t s02 = (tile->screen[0] >> 8) & 0xFF;
			int8_t s11 = tile->screen[1];
			int8_t s12 = (tile->screen[1] >> 8) & 0xFF;
			int8_t c21 = tile->coords[2];
			int8_t c22 = (tile->coords[2] >> 8) & 0xFF;
			int8_t c31 = tile->coords[3];
			int8_t c32 = (tile->coords[3] >> 8) & 0xFF;
			fout << s02 << s01 << s12 << s11;
			fout << c22 << c21 << c32 << c31;
			if (!tile->flip)
			{
				for (int y = 0; y < tile->coords[3]; y++)
				{
					for (int x = 0; x < tile->coords[2]; x++)
					{
						uint8_t idx = 0;
						FreeImage_GetPixelIndex(pSrcImage, x + tile->coords[0], y + tile->coords[1], &idx);
						fout << idx;
					}
				}
			}
			else
			{
				for (int y = 0; y < tile->coords[3]; y++)
				{
					for (int x = tile->coords[2] - 1; x >= 0; x--)
					{
						uint8_t idx = 0;
						FreeImage_GetPixelIndex(pSrcImage, x + tile->coords[0], y + tile->coords[1], &idx);
						fout << idx;
					}
				}
			}
		}
	}
	fout.close();
}


uint8_t SmitED::CWallViewer::GetTypeIndex(std::string& typeStr)
{
	
	typeStr = str_tolower(typeStr);
	if (typeStr.find("wall") != std::string::npos)
		return 1;
	if (typeStr.find("ground") != std::string::npos)
		return 0;
	if (typeStr.find("floor") != std::string::npos)
		return 0;
	if (typeStr.find("ceiling") != std::string::npos)
		return 0;
	if (typeStr.find("closed") != std::string::npos)
		return 2;
	if (typeStr.find("open") != std::string::npos)
		return 3;
	if (typeStr.find("door") != std::string::npos)
		return 2;
	
	// all others are objects
	return 5;
}

void SmitED::CWallViewer::OnDataSet()
{
	// Load the data in.


}

