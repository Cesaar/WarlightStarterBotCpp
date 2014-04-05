#include "stdafx.h"
#include "AttackTransferMove.h"

#include <sstream>
#include "Region.h"

AttackTransferMove::AttackTransferMove(string inPlayerName, Region* inFromRegion, Region* inToRegion, int inArmySize):
	Move(inPlayerName),
	mpFromRegion(inFromRegion),
	mpToRegion(inToRegion),
	mArmySize(inArmySize)
{
}


AttackTransferMove::~AttackTransferMove(void)
{
}

string AttackTransferMove::GetString() const
{
	stringstream buffer;
	if(mIllegalMove == "")
	{
		buffer << mPlayerName << " attack/transfer " << mpFromRegion->GetID() << " " << mpToRegion->GetID() << " " << mArmySize;
	}
	else
	{
		buffer << mPlayerName << " illegal_move " << mIllegalMove; 
	}

	return buffer.str();
}