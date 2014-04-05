#pragma once

#include <vector>
#include <string>
using namespace std;

class SuperRegion;

class Region
{
public:
	Region(int inID, SuperRegion* inpSuperRegion);
	Region(int inID, SuperRegion* inpSuperRegion, string inOwner, int inArmySize);
	
	virtual					~Region(void);

	void					AddNeighbor(Region* inpNeighbor);
	bool					IsNeighbor(Region* inpRegion) const;
	bool					IsOwner(string inPlayer) const;

	//getters and setters
	void					SetArmySize(int inNewSize)			{ mArmySize = inNewSize; }
	int						GetArmySize() const					{ return mArmySize; }

	void					SetOwner(string inNewOwner)			{ mOwner = inNewOwner; }
	const string&			GetOwner() const					{ return mOwner; }

	int						GetID() const						{ return mID; }

	const vector<Region*>&	GetNeighbors() const				{ return mNeighbors; }

	const SuperRegion*		GetSuperRegion() const				{ return mpMySuperRegion; }

	bool					Equals(Region* inpOtherRegion) const;
private:
	int					mID;
	vector<Region*>		mNeighbors;
	SuperRegion*		mpMySuperRegion;		
	int					mArmySize;
	string				mOwner;
};

