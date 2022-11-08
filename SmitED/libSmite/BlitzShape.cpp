#include "BlitzShape.h"
#include "common.h"
#include <stdio.h>
sBlitzShape::sBlitzShape()
	: width(0),
	height(0)
{
	chunkyBuffer = nullptr;
	memset(this, 0, sizeof(sBlitzShape));
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

void addShapeToShapes(sBlitzShapes* pShapes, sBlitzShape* pShape)
{
	pShapes->m_vecShapes.emplace_back(pShape);
}

sBlitzShapes* LoadShapes(const char* sFilename)
{

	sBlitzShapes* pShapes = new sBlitzShapes();
	FILE* fp;
	fopen_s(&fp, sFilename, "rb");
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
			addShapeToShapes(pShapes, pShape);

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
			pShape->bitmapRawData = new uint8_t[bitmapsize];
			fread(pShape->bitmapRawData, bitmapsize, 1, fp);
			//fseek(fp, bitmapsize, SEEK_CUR);

			if (ftell(fp) >= fsize)
				break;
		}
	}

	return pShapes;
}

sBlitzShapes::sBlitzShapes()
{

}

bool sBlitzShapes::doPlanarToChunky()
{
	for (auto& shape : m_vecShapes)
	{
		if (shape->width == 0 || shape->height == 0)
			continue;
		if (shape->chunkyBuffer == nullptr)
		{
			// All amiga-gfx uses palettes.
			// so only 1 byte per pixel.
			shape->chunkyBuffer = new uint8_t[(shape->width) * shape->height];
			memset(shape->chunkyBuffer, 0, sizeof(uint8_t) * (shape->width) * shape->height);

		}
		int pitch = (shape->onebpmem/shape->height);
		for (int plane = 0; plane < shape->depth; plane++)
		{
			unsigned int count = 0;
			uint32_t indexBit = 1 << plane;
			unsigned int vOffset = 0;
			for (int scanline = 0; scanline < shape->height; scanline++)
			{
				unsigned int hOffset = vOffset;
				
				unsigned int pixelCount = 0;
				for (int pixel = 0; pixel < pitch; pixel++)
				{
					unsigned char bitmask = 0x80;
					for (int bit = 0; bit < 8; bit++)
					{
						uint32_t offset = (plane * shape->onebpmem) + (scanline * pitch) + pixel;
						auto bitVal = shape->bitmapRawData[offset];
						if (pixelCount < shape->width) /* We must skip the padding bits. If we have already converted sufficient pixels on this scanline, ignore the rest */
						{

							if (bitVal & bitmask)
								shape->chunkyBuffer[(scanline * (shape->width)) + (pixel * 8) + bit] |= indexBit;

							count++;
						}
						pixelCount++;
						bitmask >>= 1;
					}	
					hOffset++;
				}

				count += pitch - shape->width;

				vOffset += pitch;
			}
		}
	}

	return true;
}

bool sBlitzShapes::doChunkyToPlanar()
{
	for (auto& shape : m_vecShapes)
	{
		unsigned int i;
		unsigned int bitplaneIndex = 0;
		int bit = 7;

		for (i = 0; i < shape->width * shape->height; i++)
		{
			unsigned int j;
			uint8_t bitmask = 1 << bit;

			for (j = 0; j < shape->depth; j++)
			{
				if (shape->chunkyBuffer[i] & (1 << j)) /* Check if the current bit of the index value is set */
					shape->bitmapRawData[(j * shape->onebpmem) + bitplaneIndex] |= bitmask;  /* Modify the current bit in the bitplane byte to be 1 and leave the others untouched */
				else
					shape->bitmapRawData[(j * shape->onebpmem) + bitplaneIndex] &= ~bitmask; /* Modify the current bit in the bitplane byte to be 0 and leave the others untouched */
			}

			bit--;

			if (bit < 0)
			{
				bit = 7; /* Reset the bit counter */
				bitplaneIndex++; /* Go to the next byte in the bitplane memory */
			}
		}
	}

	return false;
}
