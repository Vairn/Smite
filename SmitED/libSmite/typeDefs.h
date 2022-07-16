#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <filesystem>
#include <minmax.h>
enum eCommands
{
	ENCOUNTER = 0xE6,   
	IDENTIFY_ITEMS = 0xE7,   
	TURN = 0xE8,   
	LAUNCHER = 0xE9,   
	ADD_ITEM = 0xEA,   
	GIVE_XP = 0xEB,   
	CHANGE_LEVEL = 0xEC,   
	REMOVE_ITEM = 0xED,   
	IF = 0xEE,   
	GOSUB = 0xEF,   
	RETURN = 0xF0,   
	END = 0xF1,   
	GOTO = 0xF2,   
	DAMAGE = 0xF3,   
	CLEAR_FLAG = 0xF5,   
	SOUND = 0xF6,   
	SET_FLAG = 0xF7,   
	MESSAGE = 0xF8,   
	STEAL_ITEM = 0xF9,   
	TELEPORT = 0xFA,   
	ADD_MONSTER = 0xFB,   
	CLOSE_DOOR = 0xFC,   
	OPEN_DOOR = 0xFD,   
	CHANGE_WALL = 0xFE,   
	SET_WALL = 0xFF,   

};


enum eIfParams
{
	  PARTY_VISIBLE = 0xDA,   
	  ROLL_DICE = 0xDB,   
	  HAS_CLASS = 0xDC,   
	  HAS_RACE = 0xDD,   
	  TRIGGER_FLAG = 0xE0,   
	  POINTER_ITEM = 0xE7,   
	  WALL_SIDE = 0xE9,   
	  PARTY_DIRECTION = 0xED,   
	  ELSE_GOTO = 0xEE,   
	  LEVEL_FLAG = 0xEF,   
	  GLOBAL_FLAG = 0xF0,   
	  PARTY_ON_POS = 0xF1,   
	  MONSTERS_ON_POS = 0xF3,   
	  ITEMS_ON_POS = 0xF5,   
	  WALL_NUMBER = 0xF7,   
	  OR = 0xF8,   
	  AND = 0xF9,   
	  GREATERTHAN = 0xFB, 
	  LESSTHAN = 0xFD, 
	  NOTEQUAL = 0xFE,   
	  EQUAL = 0xFF, 
};

struct sMonster
{

};
struct sMosterInstance
{

};


struct sMaze
{
public:
	sMaze();

	
	void loadFromFile(std::ifstream& ifsFile); 
	void saveToFile(std::ofstream& fout);

	
	//	0: N  1:E  2:S  3:W
	uint8_t walldata[1024][4];
	
	uint8_t globalflags[128];
	uint8_t levelflags[128];
	std::vector<sMonster> monArchetype;
	std::vector<sMosterInstance> monsters;
	std::vector<uint8_t> script;
	std::vector<std::string> decompiledScript;

	
	
};
