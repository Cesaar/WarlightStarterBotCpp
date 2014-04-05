#include "stdafx.h"
#include "SuperRegion.h"
#include "Region.h"

#include <string>

SuperRegion::SuperRegion(int inID, int inArmyReward):
	mID(inID),
	mArmyReward(inArmyReward)
{
}


SuperRegion::~SuperRegion(void)
{
}

void SuperRegion::AddSubRegion(Region* inpRegion)
{
	vector<Region*>::iterator it;
	for(it = mSubRegions.begin(); it != mSubRegions.end(); ++it)
	{
		Region* pRegion = *it;
		if(pRegion == inpRegion)
			return;
	}

	//region not present
	mSubRegions.push_back(inpRegion);
}

const string SuperRegion::GetSuperRegionOwner() const
{
	if(mSubRegions.size() == 0)
		return "unknown";

	string owner = mSubRegions[0]->GetOwner();
	vector<Region*>::const_iterator it;
	for(it = mSubRegions.begin(); it != mSubRegions.end(); ++it)
	{
		const Region* pRegion = *it;
		if(pRegion->GetOwner() != owner)
			return "unknown";
	}

	return owner;
}