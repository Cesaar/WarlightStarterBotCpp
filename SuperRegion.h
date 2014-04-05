#pragma once

#include <vector>
using namespace std;

class Region;

class SuperRegion
{
public:
	SuperRegion(int id, int inArmyReward);
	virtual					~SuperRegion(void);

	void					AddSubRegion(Region* inpRegion);

	const string			GetSuperRegionOwner() const;

	int						GetID() const						{ return mID; }
	int						GetArmyReward() const				{ return mArmyReward; }
	const vector<Region*>&	GetSubRegions() const				{ return mSubRegions; }

private:
	int						mID;
	int						mArmyReward;
	vector<Region*>			mSubRegions;
};

