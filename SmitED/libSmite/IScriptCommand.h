#pragma once
#include <string>
#include <vector>
#include <functional>



void encodeEncounter(std::string, uint8_t**);
void decodeEncounter(std::string, uint8_t*);

void encodeIdentifyItems(std::string, uint8_t**);
void decodeIdentifyItems(std::string, uint8_t*);

void encodeTurn(std::string, uint8_t**);
void decodeTurn(std::string, uint8_t*);

void encodeLauncher(std::string, uint8_t**);
void decodeLauncher(std::string, uint8_t*);

void encodeAddItem(std::string, uint8_t**);
void decodeAddItem(std::string, uint8_t*);

void encodeGiveXp(std::string, uint8_t**);
void decodeGiveXp(std::string, uint8_t*);

void encodeChangeLevel(std::string, uint8_t**);
void decodeChangeLevel(std::string, uint8_t*);

void encodeRemoveItem(std::string, uint8_t**);
void decodeRemoveItem(std::string, uint8_t*);

void encodeIf(std::string, uint8_t**);
void decodeIf(std::string, uint8_t*);

void encodeGosub(std::string, uint8_t**);
void decodeGosub(std::string, uint8_t*);

void encodeReturn(std::string, uint8_t**);
void decodeReturn(std::string, uint8_t*);

void encodeEnd(std::string, uint8_t**);
void decodeEnd(std::string, uint8_t*);

void encodeGoto(std::string, uint8_t**);
void decodeGoto(std::string, uint8_t*);

void encodeDamage(std::string, uint8_t**);
void decodeDamage(std::string, uint8_t*);

void encodeClearFlag(std::string, uint8_t**);
void decodeClearFlag(std::string, uint8_t*);

void encodeSound(std::string, uint8_t**);
void decodeSound(std::string, uint8_t*);

void encodeSetFlag(std::string, uint8_t**);
void decodeSetFlag(std::string, uint8_t*);

void encodeMessage(std::string, uint8_t**);
void decodeMessage(std::string, uint8_t*);

void encodeStealItem(std::string, uint8_t**);
void decodeStealItem(std::string, uint8_t*);

void encodeTeleport(std::string, uint8_t**);
void decodeTeleport(std::string, uint8_t*);

void encodeAddMonster(std::string, uint8_t**);
void decodeAddMonster(std::string, uint8_t*);

void encodeCloseDoor(std::string, uint8_t**);
void decodeCloseDoor(std::string, uint8_t*);

void encodeOpenDoor(std::string, uint8_t**);
void decodeOpenDoor(std::string, uint8_t*);

void encodeChangeWall(std::string, uint8_t**);
void decodeChangeWall(std::string, uint8_t*);

void encodeSetWall(std::string, uint8_t**);
void decodeSetWall(std::string, uint8_t*);


class IScriptCommand
{
public:
	IScriptCommand(void);
	IScriptCommand(const std::string& sName, const uint8_t cmdId, int paramaterSize, std::function<void(std::string, uint8_t**)> encoder, std::function<void(std::string, uint8_t*)> decoder);
	virtual ~IScriptCommand(void);

	virtual bool Run(float dt);

	std::string BuildFromData(uint8_t* pSriptData);
	bool BuildFromString(std::string sScriptData, uint8_t** pBytes);

	const std::string& GetCommandName() { return m_sName; }
	
	const uint8_t GetCommandCode() { return m_cCommandCode; }
protected:
	std::string m_sName;
	uint8_t m_cCommandCode;
	char m_cOpCode;
	unsigned int m_uiOffset;
	uint8_t m_uiCmdSize;
	std::function<void(std::string, uint8_t**)> m_Encoder;
	std::function<void(std::string, uint8_t*)> m_Decoder;
	
};
/*
class CScriptSetWall : public IScriptCommand
{
public:
	CScriptSetWall(void);
	virtual ~CScriptSetWall(void);

	virtual bool Run( float dt );
	virtual bool BuildFromData( char* pSriptData );
	virtual bool BuildFromString( std::string sScriptData );
	virtual unsigned int SaveToData( char **pScriptData );
	virtual const std::string& WriteToString( void );
};

class CScriptExchangeWall : public IScriptCommand
{
public:
	CScriptExchangeWall(void);
	virtual ~CScriptExchangeWall(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptCreateMonster : public IScriptCommand
{
public:
	CScriptCreateMonster(void);
	virtual ~CScriptCreateMonster(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptTeleport: public IScriptCommand
{
public:
	CScriptTeleport(void);
	virtual ~CScriptTeleport(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptStealSmallItem: public IScriptCommand
{
public:
	CScriptStealSmallItem(void);
	virtual ~CScriptStealSmallItem(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptSetFlag: public IScriptCommand
{
public:
	CScriptSetFlag(void);
	virtual ~CScriptSetFlag(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptPlaySound : public IScriptCommand
{
public:
	CScriptPlaySound(void);
	virtual ~CScriptPlaySound(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptClearFlag: public IScriptCommand
{
public:
	CScriptClearFlag(void);
	virtual ~CScriptClearFlag(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptHealParty: public IScriptCommand
{
public:
	CScriptHealParty(void);
	virtual ~CScriptHealParty(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptDamageParty: public IScriptCommand
{
public:
	CScriptDamageParty(void);
	virtual ~CScriptDamageParty(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptElse: public IScriptCommand
{
public:
	CScriptElse(void);
	virtual ~CScriptElse(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptEndFunc: public IScriptCommand
{
public:
	CScriptEndFunc(void);
	virtual ~CScriptEndFunc(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptCallSub: public IScriptCommand
{
public:
	CScriptCallSub(void);
	virtual ~CScriptCallSub(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptReturnSub: public IScriptCommand
{
public:
	CScriptReturnSub(void);
	virtual ~CScriptReturnSub(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptCondition: public IScriptCommand
{
public:
	CScriptCondition(void);
	virtual ~CScriptCondition(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptItemConsume: public IScriptCommand
{
public:
	CScriptItemConsume(void);
	virtual ~CScriptItemConsume(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptChangeLevel: public IScriptCommand
{
public:
	CScriptChangeLevel(void);
	virtual ~CScriptChangeLevel(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptGiveExperience: public IScriptCommand
{
public:
	CScriptGiveExperience(void);
	virtual ~CScriptGiveExperience(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptCreateItem: public IScriptCommand
{
public:
	CScriptCreateItem(void);
	virtual ~CScriptCreateItem(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptThrow: public IScriptCommand
{
public:
	CScriptThrow(void);
	virtual ~CScriptThrow(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptTurn: public IScriptCommand
{
public:
	CScriptTurn(void);
	virtual ~CScriptTurn(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptIdentifyItems: public IScriptCommand
{
public:
	CScriptIdentifyItems(void);
	virtual ~CScriptIdentifyItems(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptMenu: public IScriptCommand
{
public:
	CScriptMenu(void);
	virtual ~CScriptMenu(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptWait: public IScriptCommand
{
public:
	CScriptWait(void);
	virtual ~CScriptWait(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptUpdateScreen: public IScriptCommand
{
public:
	CScriptUpdateScreen(void);
	virtual ~CScriptUpdateScreen(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptEncounters: public IScriptCommand
{
public:
	CScriptEncounters(void);
	virtual ~CScriptEncounters(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString( void );

};

class CScriptSpecialWinPics: public IScriptCommand
{
public:
	CScriptSpecialWinPics(void);
	virtual ~CScriptSpecialWinPics(void);

	virtual bool Run( float dt );

	virtual bool BuildFromData( char* pSriptData );

	virtual bool BuildFromString( std::string sScriptData );

	virtual unsigned int SaveToData( char **pScriptData );

	virtual const std::string& WriteToString(void);

};*/

class CScriptRoutine
{
public:
	struct sError
	{
		int line;
		std::string sError;
	};

	CScriptRoutine(void);
	virtual ~CScriptRoutine(void);

	bool Run(float dt);
	int Compile(std::string sScript, std::vector<sError>& vecResults);
	bool addCommand(const uint8_t cmdId, const std::string& sName, int paramaterSize, std::function<void(std::string, uint8_t **)> encoder, std::function<void(std::string, uint8_t*)>decoder);
protected:
	IScriptCommand* isKeyword(const std::string& line);

private:
	std::vector<IScriptCommand*> m_vecCommands;
};

class CScriptDecompiler
{
protected:
	IScriptCommand* eventDecodeSetWall(char *code);
	IScriptCommand* eventDecodeExchangeWall(char *code);
	IScriptCommand* eventDecodeCreateMonster(char *code);
	IScriptCommand* eventDecodeTeleport(char *code);
	IScriptCommand* eventDecodeStealSmallItem(char *code);
	IScriptCommand* eventDecodeMessage(char *code);
	IScriptCommand* eventDecodeSetFlag(char *code);
	IScriptCommand* eventDecodePlaySound(char *code);
	IScriptCommand* eventDecodeClearFlag(char *code);
	IScriptCommand* eventDecodeHealParty(char *code);
	IScriptCommand* eventDecodeDamagePartyEffect(char *code);
	IScriptCommand* eventDecodeElse(char *code);
	IScriptCommand* eventDecodeEndFunc(char *code);
	IScriptCommand* eventDecodeReturnSub(char *code);
	IScriptCommand* eventDecodeCallSub(char *code);
	IScriptCommand* eventDecodeCondition(char *code);
	IScriptCommand* eventDecodeItemConsume(char *code);
	IScriptCommand* eventDecodeChangeLevel(char *code);
	IScriptCommand* eventDecodeGiveExperience(char *code);
	IScriptCommand* eventDecodeCreateItem(char *code);
	IScriptCommand* eventDecodeThrow(char *code);
	IScriptCommand* eventDecodeTurn(char *code);
	IScriptCommand* eventDecodeIdentifyItems(char *code);
	IScriptCommand* eventDecodeMenu(char *code);
	IScriptCommand* eventDecodeWait(char *code);
	IScriptCommand* eventDecodeUpdateScreen(char *code);
	IScriptCommand* eventDecodeEncounters(char *code);
	IScriptCommand* eventDecodeSpecialWinPics(char *code);

};