#pragma once
#include <vector>
#include <string>

/*
; COMMANDS USED IN EVENT SCRIPTS
; ==============================

;  E6   ENCOUNTER
;  E7   IDENTIFY_ITEMS
;  E8   TURN
;  E9   LAUNCHER
;  EA   ADD_ITEM
;  EB   GIVE_XP
;  EC   CHANGE_LEVEL
;  ED   REMOVE_ITEM
;  EE   IF
;  EF   GOSUB
;  F0   RETURN
;  F1   END
;  F2   GOTO
;  F3   DAMAGE
;  F5   CLEAR_FLAG
;  F6   SOUND
;  F7   SET_FLAG
;  F8   MESSAGE
;  F9   STEAL_ITEM
;  FA   TELEPORT
;  FB   ADD_MONSTER
;  FC   CLOSE_DOOR
;  FD   OPEN_DOOR
;  FE   CHANGE_WALL
;  FF   SET_WALL


; IF() BLOCK PARAMETERS
; ======================

;  DA   PARTY_VISIBLE
;  DB   ROLL_DICE
;  DC   HAS_CLASS
;  DD   HAS_RACE
;  E0   TRIGGER_FLAG
;  E7   POINTER_ITEM
;  E9   WALL_SIDE
;  ED   PARTY_DIRECTION
;  EE   ELSE_GOTO
;  EF   LEVEL_FLAG
;  F0   GLOBAL_FLAG
;  F1   PARTY_ON_POS
;  F3   MONSTERS_ON_POS
;  F5   ITEMS_ON_POS
;  F7   WALL_NUMBER
;  F8   OR
;  F9   AND
;  FB >
;  FD <
	;  FE   <>
	;  FF =
	*/
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
	// bits 12 34 56 78 
	//		N  E  S  W
	uint8_t walldata[1024];
	uint8_t coldata[1024];

	uint8_t globalflags[128];
	uint8_t levelflags[128];
	std::vector<sMonster> monArchetype;
	std::vector<sMosterInstance> monsters;
	std::vector<uint8_t> script;
	std::vector<std::string> decompiledScript;
};
