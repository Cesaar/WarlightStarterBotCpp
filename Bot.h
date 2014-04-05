#pragma once

#include <vector>
using namespace std;

class Region;
class BotState;
class PlaceArmiesMove;
class AttackTransferMove;

class Bot
{
public:
	Bot();
	virtual ~Bot(void);

	vector<Region*>				GetPreferredStartingRegions(BotState* inpBotState, long timeOut);
	vector<PlaceArmiesMove*>	GetPlaceArmiesMoves(BotState* inpBotState, long timeOut);
	vector<AttackTransferMove*>	getAttackTransferMoves(BotState* inpBotState, long timeOut);
private:

};

