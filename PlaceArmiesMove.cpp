#include "stdafx.h"
#include "PlaceArmiesMove.h"

#include <sstream>
#include "Region.h"


PlaceArmiesMove::PlaceArmiesMove(string inPlayerName, Region* inpRegion, int inArmySize):
	Move(inPlayerName),
	mpRegion(inpRegion),
	mArmySize(inArmySize)
{
}


PlaceArmiesMove::~PlaceArmiesMove(void)
{
}
string PlaceArmiesMove::GetString() const
{
	stringstream buffer;
	if(mIllegalMove == "")
	{
		buffer << mPlayerName << " place_armies " << mpRegion->GetID() << " " << mArmySize;
	}
	else
	{
		buffer << mPlayerName << " illegal_move " << mIllegalMove;
	}
	return buffer.str();
}