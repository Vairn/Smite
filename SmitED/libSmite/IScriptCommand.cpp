#include "IScriptCommand.h"

#include <boost/tokenizer.hpp>
//////////////////////////////////////////////////////////////////////////

IScriptCommand::IScriptCommand(void)
{
}

IScriptCommand::IScriptCommand(const std::string& sName, const uint8_t cmdId, int paramaterSize, std::function<void(std::string, uint8_t**)> encoder, std::function<void(std::string, uint8_t*)> decoder)
{
	m_cCommandCode = cmdId;
	m_sName = sName;
	m_uiCmdSize = paramaterSize;
	m_Encoder = encoder;
	m_Decoder = decoder;
}

IScriptCommand::~IScriptCommand(void)
{
}
bool IScriptCommand::Run(float dt)
{
	return false;
}
std::string IScriptCommand::BuildFromData(uint8_t* pSriptData)
{
	if (m_Decoder)
	{
		std::string sScriptCommand;
		m_Decoder(sScriptCommand, pSriptData);
		return sScriptCommand;
	}

	return "";
}
bool IScriptCommand::BuildFromString(std::string sScriptData, uint8_t** pBytes)
{
	//uint8_t *pBytes;
	if (m_Encoder)
	{
		m_Encoder(sScriptData, pBytes);
		return true;
	}
	return false;
}
/*
//////////////////////////////////////////////////////////////////////////

CScriptSetWall::CScriptSetWall( void )
{

}

CScriptSetWall::~CScriptSetWall( void )
{

}

bool CScriptSetWall::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptSetWall::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptSetWall::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptSetWall::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptSetWall::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}


//////////////////////////////////////////////////////////////////////////


bool CScriptExchangeWall::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptExchangeWall::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptExchangeWall::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptExchangeWall::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptExchangeWall::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptExchangeWall::~CScriptExchangeWall( void )
{

}

CScriptExchangeWall::CScriptExchangeWall( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptCreateMonster::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptCreateMonster::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptCreateMonster::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptCreateMonster::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptCreateMonster::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptCreateMonster::~CScriptCreateMonster( void )
{

}

CScriptCreateMonster::CScriptCreateMonster( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptTeleport::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptTeleport::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptTeleport::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptTeleport::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptTeleport::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptTeleport::~CScriptTeleport( void )
{

}

CScriptTeleport::CScriptTeleport( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptStealSmallItem::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptStealSmallItem::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptStealSmallItem::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptStealSmallItem::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptStealSmallItem::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptStealSmallItem::~CScriptStealSmallItem( void )
{

}

CScriptStealSmallItem::CScriptStealSmallItem( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptSetFlag::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptSetFlag::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptSetFlag::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptSetFlag::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptSetFlag::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptSetFlag::CScriptSetFlag( void )
{

}

CScriptSetFlag::~CScriptSetFlag( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptPlaySound::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptPlaySound::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptPlaySound::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptPlaySound::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptPlaySound::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptPlaySound::~CScriptPlaySound( void )
{

}

CScriptPlaySound::CScriptPlaySound( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptClearFlag::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptClearFlag::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptClearFlag::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptClearFlag::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptClearFlag::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptClearFlag::~CScriptClearFlag( void )
{

}

CScriptClearFlag::CScriptClearFlag( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptHealParty::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptHealParty::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptHealParty::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptHealParty::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptHealParty::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptHealParty::CScriptHealParty( void )
{

}

CScriptHealParty::~CScriptHealParty( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptDamageParty::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptDamageParty::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptDamageParty::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptDamageParty::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptDamageParty::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptDamageParty::~CScriptDamageParty( void )
{

}

CScriptDamageParty::CScriptDamageParty( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptElse::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptElse::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptElse::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptElse::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptElse::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptElse::~CScriptElse( void )
{

}

CScriptElse::CScriptElse( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptEndFunc::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptEndFunc::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptEndFunc::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptEndFunc::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptEndFunc::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptEndFunc::~CScriptEndFunc( void )
{

}

//////////////////////////////////////////////////////////////////////////

bool CScriptCallSub::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptCallSub::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptCallSub::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptCallSub::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptCallSub::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptCallSub::CScriptCallSub( void )
{

}

CScriptCallSub::~CScriptCallSub(void)
{
}

//////////////////////////////////////////////////////////////////////////

bool CScriptReturnSub::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptReturnSub::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptReturnSub::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptReturnSub::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptReturnSub::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

CScriptReturnSub::CScriptReturnSub( void )
{

}

CScriptReturnSub::~CScriptReturnSub( void )
{

}

//////////////////////////////////////////////////////////////////////////

CScriptCondition::CScriptCondition( void )
{

}

CScriptCondition::~CScriptCondition( void )
{

}

bool CScriptCondition::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptCondition::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptCondition::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptCondition::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptCondition::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptItemConsume::CScriptItemConsume( void )
{

}

CScriptItemConsume::~CScriptItemConsume( void )
{

}

bool CScriptItemConsume::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptItemConsume::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptItemConsume::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptItemConsume::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptItemConsume::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptChangeLevel::CScriptChangeLevel( void )
{

}

CScriptChangeLevel::~CScriptChangeLevel( void )
{

}

bool CScriptChangeLevel::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptChangeLevel::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptChangeLevel::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptChangeLevel::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptChangeLevel::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptGiveExperience::CScriptGiveExperience( void )
{

}

CScriptGiveExperience::~CScriptGiveExperience( void )
{

}

bool CScriptGiveExperience::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptGiveExperience::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptGiveExperience::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptGiveExperience::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptGiveExperience::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptCreateItem::CScriptCreateItem( void )
{

}

CScriptCreateItem::~CScriptCreateItem( void )
{

}

bool CScriptCreateItem::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptCreateItem::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptCreateItem::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptCreateItem::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptCreateItem::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptThrow::CScriptThrow( void )
{

}

CScriptThrow::~CScriptThrow( void )
{

}

bool CScriptThrow::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptThrow::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptThrow::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptThrow::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptThrow::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptTurn::CScriptTurn( void )
{

}

CScriptTurn::~CScriptTurn( void )
{

}

bool CScriptTurn::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptTurn::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptTurn::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptTurn::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptTurn::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptIdentifyItems::CScriptIdentifyItems( void )
{

}

CScriptIdentifyItems::~CScriptIdentifyItems( void )
{

}

bool CScriptIdentifyItems::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptIdentifyItems::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptIdentifyItems::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptIdentifyItems::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptIdentifyItems::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptMenu::CScriptMenu( void )
{

}

CScriptMenu::~CScriptMenu( void )
{

}

bool CScriptMenu::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptMenu::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptMenu::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptMenu::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptMenu::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptWait::CScriptWait( void )
{

}

CScriptWait::~CScriptWait( void )
{

}

bool CScriptWait::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptWait::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptWait::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptWait::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptWait::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptUpdateScreen::CScriptUpdateScreen( void )
{

}

CScriptUpdateScreen::~CScriptUpdateScreen( void )
{

}

bool CScriptUpdateScreen::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptUpdateScreen::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptUpdateScreen::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptUpdateScreen::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptUpdateScreen::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptEncounters::CScriptEncounters( void )
{

}

CScriptEncounters::~CScriptEncounters( void )
{

}

bool CScriptEncounters::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptEncounters::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptEncounters::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptEncounters::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptEncounters::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}

//////////////////////////////////////////////////////////////////////////

CScriptSpecialWinPics::CScriptSpecialWinPics( void )
{

}

CScriptSpecialWinPics::~CScriptSpecialWinPics( void )
{

}

bool CScriptSpecialWinPics::Run( float dt )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptSpecialWinPics::BuildFromData( char* pSriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

bool CScriptSpecialWinPics::BuildFromString( std::string sScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

unsigned int CScriptSpecialWinPics::SaveToData( char **pScriptData )
{
	throw std::exception("The method or operation is not implemented.");
}

const std::string& CScriptSpecialWinPics::WriteToString( void )
{
	throw std::exception("The method or operation is not implemented.");
}
*/

CScriptRoutine::CScriptRoutine(void)
{
	m_vecCommands.clear();
}

CScriptRoutine::~CScriptRoutine(void)
{
	m_vecCommands.clear();
}

bool CScriptRoutine::Run(float dt)
{
	return false;
}

int CScriptRoutine::Compile(std::string sScript, std::vector<sError>& vecResults)
{
	using namespace boost;
	vecResults.clear();
	std::string sNewLine;
	char_separator<char> sep("\n");
	tokenizer<char_separator<char>> tokens(sScript, sep);

	for (auto line : tokens) {
		sNewLine = line;
		IScriptCommand* cmd = isKeyword(line);
		if(cmd != nullptr)
		{
			uint8_t* pCmdBytes;
			cmd->BuildFromString(line, &pCmdBytes);
			
		}
	}
	// returns 0 on success, or the amount of errors it detected;
	return vecResults.size();
}

bool CScriptRoutine::addCommand(const uint8_t cmdId, const std::string& sName, int paramaterSize, std::function<void(std::string, uint8_t**)> encoder, std::function<void(std::string, uint8_t*)> decoder)
{
	IScriptCommand* pNewCommand = new IScriptCommand(sName, cmdId, paramaterSize, encoder, decoder);
	
	m_vecCommands.emplace_back(pNewCommand);
	return true;
}

inline IScriptCommand* CScriptRoutine::isKeyword(const std::string& line)
{
	using namespace boost;

	char_separator<char> lineSep(" \t(,)");
	tokenizer<char_separator<char>> lineWords(line, lineSep);

	for (auto& word : lineWords) {
		for (auto pCommand : m_vecCommands)
		{
			if (word.compare(pCommand->GetCommandName()) == 0)
				return pCommand;
		}
	}

	return nullptr;
}

