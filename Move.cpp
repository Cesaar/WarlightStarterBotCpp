#include "stdafx.h"
#include "Move.h"


Move::Move(string inPlayerName):
	mPlayerName(inPlayerName)
{
	mIllegalMove = "";
}


Move::~Move(void)
{
}
