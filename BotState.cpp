#include "stdafx.h"
#include "BotState.h"

#include "Region.h"
#include "SuperRegion.h"
#include "Map.h"
#include "PlaceArmiesMove.h"
#include "AttackTransferMove.h"

BotState::BotState():
	mRoundNumber(0)
{
	mFullMap = new Map();
	mVisibleMap = new Map();
}


BotState::~BotState(void)
{
}
void BotState::UpdateSettings(string key, string value)
{
	if(key == "your_bot") //bot's own name
		mMyName = value;
	else if(key == "opponent_bot") //opponents name
		mOpponentName = value;
	else if(key == "starting_armies")
	{
		mStartingArmies = stoi(value);
		++mRoundNumber; //next round
	}
}
 // Initial map is given to the bot with all the information except for player and armies info
void BotState::SetupMap(const vector<string>& inMapInput)
{
	int regionID, superRegionID, reward;

	if(inMapInput[1] == "super_regions")
	{
		for(size_t i = 2; i < inMapInput.size(); ++i)
		{
			superRegionID = stoi(inMapInput[i]);
			++i;
			reward = stoi(inMapInput[i]);
			mFullMap->AddSuperRegion(new SuperRegion(superRegionID, reward));
		}
	}
	else if(inMapInput[1] == "regions")
	{
		for(size_t i = 2; i < inMapInput.size(); ++i)
		{
			regionID = stoi(inMapInput[i]);
			++i;
			superRegionID = stoi(inMapInput[i]);
			SuperRegion* pSuperRegion = mFullMap->GetSuperRegion(superRegionID);
			if(pSuperRegion == nullptr) continue;
			mFullMap->AddRegion(new Region(regionID, pSuperRegion));
		}
	}
	else if(inMapInput[1] == "neighbors")
	{
		for(size_t i = 2; i < inMapInput.size(); ++i)
		{
			Region* pRegion = mFullMap->GetRegion(stoi(inMapInput[i]));
			if(pRegion == nullptr) break;
			i++;
			stringstream ss(inMapInput[i]);
			string item;
			vector<string> neighbors_vector;
			while(getline(ss, item, ','))
				neighbors_vector.push_back(item);
			for(size_t j = 0; j < neighbors_vector.size(); ++j)
			{
				Region* pNeighbor = mFullMap->GetRegion(stoi(neighbors_vector[j]));
				if(pNeighbor == nullptr) continue;
				pRegion->AddNeighbor(pNeighbor);
			}				
		}
	}
}
void BotState::SetPickableStartingRegions(const vector<string>& inMapInput)
{
	for(size_t i = 2; i < inMapInput.size(); ++i)
	{
		int regionID = stoi(inMapInput[i]);
		Region* pRegion = mFullMap->GetRegion(regionID);
		if(pRegion == nullptr) continue;
		mPickableStartingRegions.push_back(pRegion);
	}
}
// Visible regions are given to the bot with player and armies info
void BotState::UpdateMap(const vector<string>& inMapInput)
{
	mFullMap->GetMapCopy(mVisibleMap);
	for(size_t i = 1; i < inMapInput.size(); ++i)
	{
		Region* pRegion = mVisibleMap->GetRegion(stoi(inMapInput[i]));
		if(pRegion == nullptr) break;
		string playerName = inMapInput[i + 1];
		int armies = stoi(inMapInput[i + 2]);

		pRegion->SetOwner(playerName);
		pRegion->SetArmySize(armies);
		i += 2;
	}
	vector<Region*> unknownRegions;
	list<Region*>::const_iterator it;
	for(it = mVisibleMap->GetRegions().begin(); it != mVisibleMap->GetRegions().end(); ++it)
	{
		Region* pRegion = *it;
		if(pRegion->GetOwner() == "unknown")
			unknownRegions.push_back(pRegion);
	}
	vector<Region*>::const_iterator it2;
	for(it2 = unknownRegions.begin(); it2 != unknownRegions.end(); ++it2)
	{
		Region* pRegion = *it2;
		mVisibleMap->RemoveRegion(pRegion);
	}

}
// Parses a list of the opponent's moves every round. 
// Clears it at the start, so only the moves of this round are stored.
void BotState::ReadOpponentMoves(const vector<string>& inMoveInput)
{
	//clear the previous moves
	vector<Move*>::iterator it;
	for(it = mOpponentMoves.begin(); it != mOpponentMoves.end(); ++it)
	{
		Move* pMove = *it;
		delete pMove;
	}
	mOpponentMoves.clear();
	for(size_t i = 1; i < inMoveInput.size(); ++i)
	{
		Move* pMove;
		if(inMoveInput[i + 1] == "place_armies")
		{
			Region* pRegion = mVisibleMap->GetRegion(stoi(inMoveInput[i + 2]));
			if(pRegion == nullptr) break;
			string playerName = inMoveInput[i];
			int armies = stoi(inMoveInput[i + 3]);
			pMove = new PlaceArmiesMove(playerName, pRegion, armies);
			i += 3;
		}
		else if(inMoveInput[i + 1] == "attack/transfer")
		{
			Region* pFromRegion = mFullMap->GetRegion(stoi(inMoveInput[i + 2]));
			if(pFromRegion == nullptr) break;

			Region* pToRegion = mFullMap->GetRegion(stoi(inMoveInput[i + 3]));
			if(pToRegion == nullptr) break;

			string playerName = inMoveInput[i];
			int armies = stoi(inMoveInput[i + 4]);
			pMove = new AttackTransferMove(playerName, pFromRegion, pToRegion, armies);
			i += 4;
		}
		else
			continue;

		mOpponentMoves.push_back(pMove);
	}
}