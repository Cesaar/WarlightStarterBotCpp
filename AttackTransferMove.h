#pragma once

#include "Move.h"

class Region;

class AttackTransferMove : public Move
{
public:
	AttackTransferMove(string inPlayerName, Region* inFromRegion, Region* inToRegion, int inArmySize);
	virtual ~AttackTransferMove(void);

	int				GetArmySize() const					{ return mArmySize; }
	Region*			GetFromRegion() const				{ return mpFromRegion; }
	Region*			GetToRegion() const					{ return mpToRegion; }

	string			GetString() const;

private:
	Region*		mpFromRegion;
	Region*		mpToRegion;
	int			mArmySize;
};

