#pragma once

#include <vector>
#include <list>
using namespace std;

class Region;
class SuperRegion;

class Map
{
public:
	Map();
	Map(list<Region*> inRegions, vector<SuperRegion*> inSuperRegions);
	virtual							~Map(void);

	void							AddRegion(Region* inpRegion);
	void							AddSuperRegion(SuperRegion* inpSuperRegion);

	void							GetMapCopy(Map* outMapCopy) const;

	Region*							GetRegion(int inID) const;
	SuperRegion*					GetSuperRegion(int inID) const;

	const list<Region*>&			GetRegions() const								{ return mRegions; }
	const vector<SuperRegion*>&		GetSuperRegions() const							{ return mSuperRegions; }

	void							RemoveRegion(Region* inpRegion);			
private:
	list<Region*>			mRegions;
	vector<SuperRegion*>	mSuperRegions;

};

