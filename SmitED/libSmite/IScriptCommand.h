#pragma once
#include <string>
#include <vector>

class IScriptCommand
{
public:
	IScriptCommand(void);
	virtual ~IScriptCommand(void);

	virtual bool Run(float dt) = 0;

	virtual bool BuildFromData(char* pSriptData) = 0;
	virtual bool BuildFromString(std::string sScriptData) =0;
	virtual unsigned int SaveToData(char **pScriptData) = 0;

	virtual const std::string& WriteToString(void) = 0;
protected:
	char m_cCommandCode;
	char m_cOpCode;
	unsigned int m_uiOffset;
};

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

};

class CScriptRoutine
{
public:
	CScriptRoutine(void);
	virtual ~CScriptRoutine(void);

	bool Run(float dt);
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