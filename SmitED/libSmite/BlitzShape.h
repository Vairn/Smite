#pragma once
#include <cstdint>
#include <vector>
struct sBlitzShape
{
	sBlitzShape();

	void swapValues();
	uint16_t width, height, depth, ebWidth, bltsize ,xhandle, yhandle;
	uint8_t unknown[8];
	uint16_t onebpmem, onebpmemx, allmem, allmemx, isReal;
	

};

struct sBlitzShapes
{
	std::vector<sBlitzShape*> shapes;
};


sBlitzShapes* LoadShapes(const char* sFilename);