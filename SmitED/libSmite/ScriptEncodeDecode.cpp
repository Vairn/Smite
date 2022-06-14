#include "IScriptCommand.h"
#include <boost/tokenizer.hpp>
using namespace boost;

#define StartProcessLines(x) char_separator<char> lineSep(" \t(,)"); \
tokenizer<char_separator<char>> lineWords(x, lineSep); \
int i = 0; \
for (auto word : lineWords) \
{ \
	if (i != 0) \
	{ 

#define EndProcessingLines } i++; }


void encodeEncounter(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeEncounter(std::string sLine, uint8_t* pBytes) {}

void encodeIdentifyItems(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeIdentifyItems(std::string sLine, uint8_t* pBytes) {}

void encodeTurn(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeTurn(std::string sLine, uint8_t* pBytes) {}

void encodeLauncher(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeLauncher(std::string sLine, uint8_t* pBytes) {}

void encodeAddItem(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}


void decodeAddItem(std::string sLine, uint8_t* pBytes) 
{
	
}

void encodeGiveXp(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeGiveXp(std::string sLine, uint8_t* pBytes) {}

void encodeChangeLevel(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeChangeLevel(std::string sLine, uint8_t* pBytes) {}

void encodeRemoveItem(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeRemoveItem(std::string sLine, uint8_t* pBytes) {}

void encodeIf(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeIf(std::string sLine, uint8_t* pBytes) {}

void encodeGosub(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeGosub(std::string sLine, uint8_t* pBytes) {}

void encodeReturn(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeReturn(std::string sLine, uint8_t* pBytes) {}

void encodeEnd(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeEnd(std::string sLine, uint8_t* pBytes) {}

void encodeGoto(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeGoto(std::string sLine, uint8_t* pBytes) {}

void encodeDamage(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeDamage(std::string sLine, uint8_t* pBytes) {}

void encodeClearFlag(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeClearFlag(std::string sLine, uint8_t* pBytes) {}

void encodeSound(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeSound(std::string sLine, uint8_t* pBytes) {}

void encodeSetFlag(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeSetFlag(std::string sLine, uint8_t* pBytes) {}

void encodeMessage(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeMessage(std::string sLine, uint8_t* pBytes) {}

void encodeStealItem(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeStealItem(std::string sLine, uint8_t* pBytes) {}

void encodeTeleport(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeTeleport(std::string sLine, uint8_t* pBytes) {}

void encodeAddMonster(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeAddMonster(std::string sLine, uint8_t* pBytes) {}

void encodeCloseDoor(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeCloseDoor(std::string sLine, uint8_t* pBytes) {}

void encodeOpenDoor(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeOpenDoor(std::string sLine, uint8_t* pBytes) {}

void encodeChangeWall(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeChangeWall(std::string sLine, uint8_t* pBytes) {}

void encodeSetWall(std::string sLine, uint8_t** ppBytes)
{ 
	StartProcessLines(sLine);
			printf("Parameter %d: %s\n", i,word.c_str());
	EndProcessingLines;

}

void decodeSetWall(std::string sLine, uint8_t* pBytes) {}