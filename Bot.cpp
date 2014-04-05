#include "stdafx.h"
#include "Bot.h"

#include "Region.h"
#include "AttackTransferMove.h"
#include "PlaceArmiesMove.h"

Bot::Bot()
{
}


Bot::~Bot(void)
{
}
vector<Region*> Bot::GetPreferredStartingRegions(BotState* inpBotState, long timeOut)
{
	vector<Region*> result;
	//do stuff you want

	return result;
}
vector<PlaceArmiesMove*> Bot::GetPlaceArmiesMoves(BotState* inpBotState, long timeOut)
{
	vector<PlaceArmiesMove*> result;

	//do stuff you want

	return result;
}
vector<AttackTransferMove*> Bot::getAttackTransferMoves(BotState* inpBotState, long timeOut)
{
	vector<AttackTransferMove*> result;

	//do stuff you want

	return result;
}