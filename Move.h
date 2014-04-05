#pragma once

#include <string>
using namespace std;

class Move
{
public:
	Move(string inPlayerName);
	virtual ~Move(void);

	void				SetPlayerName(string inNewName)			{ mPlayerName = inNewName; }
	const string&		GetPlayerName() const					{ return mPlayerName; }

	void				SetIllegalMove(string inIllegalMove)	{ mIllegalMove = inIllegalMove; }
	const string&		GetIllegalMove() const					{ return mIllegalMove; }


protected:
	string mPlayerName;
	string mIllegalMove;
};

