#pragma once

#include "Move.h"

class Region;

class PlaceArmiesMove : public Move
{
public:
	PlaceArmiesMove(string inPlayerName, Region* inpRegion, int inArmySize);
	virtual ~PlaceArmiesMove(void);

	void		SetArmySize(int inNewArmySize)			{ mArmySize = inNewArmySize; }
	int			GetArmySize() const						{ return mArmySize; }

	Region*		GetRegion() const						{ return mpRegion; }

	string		GetString() const;

private:
	Region*	mpRegion;
	int		mArmySize;
};

