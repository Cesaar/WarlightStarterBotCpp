#include "stdafx.h"
#include "BotParser.h"

#include "Region.h"
#include "Bot.h"
#include "BotState.h"
#include "PlaceArmiesMove.h"
#include "AttackTransferMove.h"

#include <iostream>
#include <sstream>

BotParser::BotParser(Bot* inpBot):
	mpBot(inpBot)
{
	mpCurrentstate = new BotState();
}


BotParser::~BotParser(void)
{
}
void BotParser::Run()
{
	while(true)
	{
		string line;
		getline(cin, line);
		//trimming
		const auto strBegin = line.find_first_not_of(" \t");
		if (strBegin != std::string::npos)
		{

			const basic_string<char>::size_type  strEnd = line.find_last_not_of(" \t");
			const basic_string<char>::size_type  strRange = strEnd - strBegin + 1;

			line = line.substr(strBegin, strRange);
		}
		//splitting
		stringstream ss(line);
		string item;
		vector<string> parts;
		while(getline(ss, item, ' '))
			parts.push_back(item);

		if(parts.size() == 0) continue;

		if(parts[0] == "pick_starting_regions")
		{
			mpCurrentstate->SetPickableStartingRegions(parts);
			vector<Region*> preferredStartingRegions = mpBot->GetPreferredStartingRegions(mpCurrentstate, stol(parts[1]));
			stringstream buffer;
			vector<Region*>::iterator it;
			for(it = preferredStartingRegions.begin(); it != preferredStartingRegions.end(); ++it)
			{
				Region* pRegion = *it;
				buffer << pRegion->GetID() << " ";
			}
			cout<<buffer.str();
		}
		else if (parts.size() == 3 && parts[0] == "go")
		{
			//we need to do a move
			stringstream buffer("");
			if(parts[1] == "place_armies")
			{
				//place armies
				vector<PlaceArmiesMove*> placeArmiesMoves = mpBot->GetPlaceArmiesMoves(mpCurrentstate, stol(parts[2]));
				vector<PlaceArmiesMove*>::iterator it;
				for(it = placeArmiesMoves.begin(); it != placeArmiesMoves.end(); ++it)
				{
					PlaceArmiesMove* pMove = *it;
					buffer << pMove->GetString();
				}
			}
			else if(parts[1] == "attack/transfer")
			{
				//attack/transfer
				vector<AttackTransferMove*> attackTransferMoves = mpBot->getAttackTransferMoves(mpCurrentstate, stol(parts[2]));
				vector<AttackTransferMove*>::iterator it;
				for(it = attackTransferMoves.begin(); it != attackTransferMoves.end(); ++it)
				{
					AttackTransferMove* pMove = *it;
					buffer << pMove->GetString();
				}
			}
			if(buffer.str() == "")
				cout<<"No moves";
			else
				cout<<buffer.str();
		}
		else if (parts.size() == 3 && parts[0] == "settings")
        {
            // Update settings
			mpCurrentstate->UpdateSettings(parts[1], parts[2]);
        }
        else if (parts[0] == "setup_map")
        {
            // Initial full map is given
            mpCurrentstate->SetupMap(parts);
        }
        else if (parts[0] == "update_map")
        {
            // All visible regions are given
            mpCurrentstate->UpdateMap(parts);
        }
        else if (parts[0] == "opponent_moves")
        {
            // All visible opponent moves are given
            mpCurrentstate->ReadOpponentMoves(parts);
        }
		/*
        else
        {
            Console.Error.WriteLine("Unable to parse line \"" + line + "\"");
        }
		*/
	}
}