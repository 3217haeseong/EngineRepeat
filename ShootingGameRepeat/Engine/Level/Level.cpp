#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include "iostream"

Level::Level()
{

}

Level::~Level()
{
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}

	actors.clear();
}

void Level::AddActor(Actor* newActor)
{
	addRequestedActors.emplace_back(newActor);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	if (destroyRequestedActors.size() > 0)
	{
		for (const Actor* const actor : destroyRequestedActors)
		{
			if (actor == destroyedActor)
			{
				return;
			}
		}
	}

	destroyRequestedActors.emplace_back(destroyedActor);
}

void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		if (actor->autoDestroy)
		{
			actor->lifetime -= deltaTime;

			if (actor->lifetime <= 0.0f)
			{
				actor->lifetime = 0.0f;
				actor->Destroy();
				continue;
			}
		}

		actor->Tick(deltaTime);
	}
}

void Level::ProcessAddAndDestroyActors()
{
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		if ((*iterator)->isExpired)
		{
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	for (auto*& actor : destroyRequestedActors)
	{
		Utils::SetConsolePosition(actor->position);

		SafeDelete(actor);
	}

	destroyRequestedActors.clear();

	for (auto* const actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	addRequestedActors.clear();
}

void Level::SortActorBySortingOrder()
{
	for (int ix = 0; ix < (int)actors.size(); ++ix)
	{
		for (int jx = 0; jx < (int)actors.size() - 1; ++jx)
		{
			if (actors[jx]->sortingOrder > actors[jx + 1]->sortingOrder)
			{
				std::swap(actors[jx], actors[jx + 1]);
			}
		}
	}
}