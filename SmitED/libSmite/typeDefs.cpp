#include "typeDefs.h"

sMaze::sMaze()
{
	memset(walldata, 0, 1024*4);
	
	memset(globalflags, 0, 128);
	memset(levelflags, 0, 128);
	script.clear();
	decompiledScript.clear();
	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			int offset = (y * 32) + x;
			if (offset % 2)
			{
				walldata[offset][0] = 0x01;
				walldata[offset][1] = 0x02;
				walldata[offset][2] = 0x01;
				walldata[offset][3] = 0x02;
			}
			else
			{
				walldata[offset][0] = 0x02;
				walldata[offset][1] = 0x01;
				walldata[offset][2] = 0x02;
				walldata[offset][3] = 0x01;
			}
			/*if (y == 0)
				walldata[offset] += 0b00000001;
				
			if (x==0)
				walldata[offset] += 0b00000100;

			if (y == 31)
				walldata[offset] += 0b00010000;

			if (x == 31)
				walldata[offset] += 0b01000000;*/
		}
	}
}

void sMaze::saveToFile(std::string& sFilename)
{
	std::ofstream fout(sFilename, std::ios_base::binary);
	fout << "LVL";
	
	// level walls
	for (int i=0; i < 1024; i++)
	{
		fout << (uint8_t)walldata[i][0];
		fout << (uint8_t)walldata[i][1];
		fout << (uint8_t)walldata[i][2];
		fout << (uint8_t)walldata[i][3];
	}

	// write the size of the script
	{
		int32_t scriptLen = script.size();
		int8_t s01 = scriptLen;
		int8_t s02 = (scriptLen >> 8) & 0xFF;
		int8_t s03 = (scriptLen >> 16) & 0xFF;
		int8_t s04 = (scriptLen >> 24) & 0xFF;
		fout << s04 << s03 << s02 << s01;
	}
	// write the script bytes out
	for (uint8_t smyte : script)
	{
		fout << (uint8_t)smyte;
	}

}
