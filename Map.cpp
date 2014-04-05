#include "stdafx.h"
#include "Map.h"

#include "Region.h"
#include "SuperRegion.h"


Map::Map()
{
}
Map::Map(list<Region*> inRegions, vector<SuperRegion*> inSuperRegions)
{
	mRegions = inRegions;
	mSuperRegions = inSuperRegions;
}

Map::~Map(void)
{
	int i = 0;
}

void Map::AddRegion(Region* inpRegion)
{
	//check if the region has a valid id
	list<Region*>::iterator it;
	for(it = mRegions.begin(); it != mRegions.end(); ++it)
	{
		Region* pRegion = *it;
		if(pRegion->GetID() == inpRegion->GetID())
		{
			//delete this new region
			delete inpRegion;
			inpRegion = nullptr;
			//return
			return;
		}
	}

	mRegions.push_back(inpRegion);
}
void Map::AddSuperRegion(SuperRegion* inpSuperRegion)
{
	//check if the region has a valid id
	vector<SuperRegion*>::iterator it;
	for(it = mSuperRegions.begin(); it != mSuperRegions.end(); ++it)
	{
		SuperRegion* pSuperRegion = *it;
		if(pSuperRegion->GetID() == inpSuperRegion->GetID())
		{
			delete inpSuperRegion;
			inpSuperRegion = nullptr;
			return;
		}
	}

	mSuperRegions.push_back(inpSuperRegion);
}

void Map::GetMapCopy(Map* outMapCopy) const
{
	/*
	if(outMapCopy != nullptr)
	{
		delete outMapCopy;
	}*/

	outMapCopy = new Map();
	//copy superregions
	vector<SuperRegion*>::const_iterator it2;
	for(it2 = mSuperRegions.begin(); it2 != mSuperRegions.end(); ++it2)
	{
		SuperRegion* pSuperRegion = *it2;
		SuperRegion* pNewSuperRegion = new SuperRegion(pSuperRegion->GetID(), pSuperRegion->GetArmyReward());
		outMapCopy->AddSuperRegion(pNewSuperRegion);
	}
	//copy regions
	list<Region*>::const_iterator it1;
	for(it1 = mRegions.begin(); it1 != mRegions.end(); ++it1)
	{
		Region* pRegion = *it1;

		Region* pNewRegion = new Region(pRegion->GetID(), 
										outMapCopy->GetSuperRegion(pRegion->GetSuperRegion()->GetID()),
										pRegion->GetOwner(),
										pRegion->GetArmySize());
		outMapCopy->AddRegion(pNewRegion);
	}
	//add neighbours to copied regions
	list<Region*>::const_iterator it3;
	for(it3 = mRegions.begin(); it3 != mRegions.end(); ++it3)
	{
		Region* pRegion = *it3;
		Region* pNewRegion = outMapCopy->GetRegion(pRegion->GetID());
		vector<Region*>::const_iterator it4;
		for(it4 = pRegion->GetNeighbors().begin(); it4 != pRegion->GetNeighbors().end(); ++it4)
		{
			Region* pNeighbor = *it4;
			pNewRegion->AddNeighbor(outMapCopy->GetRegion(pNeighbor->GetID()));
		}
	}
}

Region*	Map::GetRegion(int inID) const
{
	list<Region*>::const_iterator it;
	for(it = mRegions.begin(); it != mRegions.end(); ++it)
	{
		Region* pRegion = *it;
		if(pRegion->GetID() == inID)
			return pRegion;
	}

	return nullptr;
}
SuperRegion* Map::GetSuperRegion(int inID) const
{
	vector<SuperRegion*>::const_iterator  it;
	for(it = mSuperRegions.begin(); it != mSuperRegions.end(); ++it)
	{
		SuperRegion* pSuperRegion = *it;
		if(pSuperRegion->GetID() == inID)
			return pSuperRegion;
	}

	return nullptr;
}
void Map::RemoveRegion(Region* inpRegion)
{
	list<Region*>::iterator it;
	Region* region_to_remove = nullptr;
	for(it = mRegions.begin(); it != mRegions.end(); ++it)
	{
		Region* pRegion = *it;
		if(pRegion->Equals(inpRegion))
		{
			region_to_remove = pRegion;
			break;
		}
	}
	if(region_to_remove != nullptr)
		mRegions.remove(region_to_remove);
}