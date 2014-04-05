#include "stdafx.h"
#include "Region.h"
#include "SuperRegion.h"

Region::Region(int inID, SuperRegion* inpSuperRegion):
	mID(inID),
	mpMySuperRegion(inpSuperRegion),
	mOwner("unknown"),
	mArmySize(0)
{
	inpSuperRegion->AddSubRegion(this);
}
Region::Region(int inID, SuperRegion* inpSuperRegion, string inOwner, int inArmySize):
	mID(inID),
	mpMySuperRegion(inpSuperRegion),
	mOwner(inOwner),
	mArmySize(inArmySize)
{
	inpSuperRegion->AddSubRegion(this);
}

Region::~Region(void)
{
}

void Region::AddNeighbor(Region* inpNeighbor)
{
	if(IsNeighbor(inpNeighbor))
		return;

	mNeighbors.push_back(inpNeighbor);
	inpNeighbor->AddNeighbor(this);
}
bool Region::IsNeighbor(Region* inpRegion) const
{
	vector<Region*>::const_iterator it;
	for(it = mNeighbors.begin(); it != mNeighbors.end(); ++it)
	{
		Region* pRegion = *it;
		if(pRegion == inpRegion)
			return true;
	}

	return false;
}
bool Region::IsOwner(string inPlayer) const
{
	return (inPlayer == mOwner);
}
bool Region::Equals(Region* inpOtherRegion) const
{
	if(mID != inpOtherRegion->GetID())
		return false;
	if(mArmySize != inpOtherRegion->GetArmySize())
		return false;
	if(mOwner != inpOtherRegion->GetOwner())
		return false;

	return true;
}