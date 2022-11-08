#pragma once
#include <cstdint>
#include <vector>
struct sBlitzShape
{
	sBlitzShape();

	void swapValues();
	uint16_t width, height, depth, ebWidth, bltsize, xhandle, yhandle;
	uint8_t unknown[8];
	uint16_t onebpmem, onebpmemx, allmem, allmemx, isReal;

	uint8_t* bitmapRawData;
	uint8_t* chunkyBuffer;
	uint8_t* planarBuffer;

	

};

struct sBlitzShapes
{
	sBlitzShapes();

	bool doPlanarToChunky();
	bool doChunkyToPlanar();

	std::vector<sBlitzShape*> m_vecShapes;
};


sBlitzShapes* LoadShapes(const char* sFilename);