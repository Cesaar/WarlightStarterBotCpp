#pragma once

#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Map;
class Region;
class Move;




class BotState
{
public:
	BotState();
	virtual ~BotState(void);

	void					UpdateSettings(string key, string value);
	void					SetupMap(const vector<string>& inMapInput);
	void					SetPickableStartingRegions(const vector<string>& inMapInput);
	void					UpdateMap(const vector<string>& inMapInput);
	void					ReadOpponentMoves(const vector<string>& inMoveInput);

	const string&			GetMyPlayerName() const								{ return mMyName; }
	const string&			GetOpponentPlayerName() const						{ return mOpponentName; }
	int						GetStartingArmies() const							{ return mStartingArmies; }
	int						GetRoundNumber() const								{ return mRoundNumber; }
	const Map*				GetVisibleMap() const								{ return mVisibleMap; }
	const Map*				GetFullMap() const									{ return mFullMap; }
	const vector<Move*>&	GetOpponentMoves() const							{ return mOpponentMoves; }
	const vector<Region*>&	GetPickableStartRegions() const						{ return mPickableStartingRegions; }
private:
	string				mMyName;
	string				mOpponentName;

	Map*				mFullMap;
	Map*				mVisibleMap;

	vector<Region*>		mPickableStartingRegions;
	vector<Move*>		mOpponentMoves;

	int					mStartingArmies;
	int					mRoundNumber;
};

