#pragma once

#include "core.h"
#include <vector>
#include "RTTI.h"

class Actor;
class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level,RTTI)

public:
	Level();
	virtual ~Level();

	void AddActor(Actor* newActor);

	void DestroyActor(Actor* destroyedActor);

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	void ProcessAddAndDestroyActors();

private:
	void SortActorBySortingOrder();

protected:
	std::vector<Actor*> actors;

	std::vector<Actor*> addRequestedActors;

	std::vector<Actor*> destroyRequestedActors;
};