#include "BlitzShape.h"
#include "common.h"
#include <stdio.h>
sBlitzShape::sBlitzShape()
	: width(0),
	height(0)
{
}

void sBlitzShape::swapValues()
{
	width = swap_uint16(width);
	height = swap_uint16(height);
	depth = swap_uint16(depth);
	ebWidth = swap_uint16(ebWidth);
	bltsize = swap_uint16(bltsize);
	xhandle = swap_uint16(xhandle);
	yhandle = swap_uint16(yhandle);
	onebpmem = swap_uint16(onebpmem);
	onebpmemx = swap_uint16(onebpmemx);
	allmem = swap_uint16(allmem);
	allmemx = swap_uint16(allmemx);

}

sBlitzShapes* LoadShapes(const char* sFilename)
{

	sBlitzShapes* pShapes = new sBlitzShapes();
	FILE* fp;
	fp = fopen(sFilename, "rb");
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (pShapes != nullptr && fp != nullptr)
	{
		while (1)
		{
			sBlitzShape* pShape = new sBlitzShape();

			fread(&pShape->width, 2, 16, fp);
			pShape->swapValues();
			pShapes->shapes.emplace_back(pShape);
			//fseek(fp, 20, SEEK_CUR);
			/*
			bitplanesize = C2D(ebwidth) * C2D(pixheight)
   bitmapsize = bitplanesize * C2D(depth)
   IF shape# < args.from THEN DO
      CALL Seek fh,bitmapsize,CURRENT
      ITERATE
      END*/
			int bitplanesize = pShape->ebWidth * pShape->height;
			int bitmapsize = pShape->depth * bitplanesize;
			fseek(fp, bitmapsize, SEEK_CUR);
			if (ftell(fp) >= fsize)
				break;
		}
	}

	return pShapes;
}
