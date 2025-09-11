#include "Level.h"
#include "Actor/Actor.h"

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
	actors.emplace_back(newActor);

	newActor->SetOwner(this);
}

void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
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
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	SortActorsBySortingOrder();

	for (Actor* const actor : actors)
	{
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			if (actor == otherActor)
			{
				continue;
			}

			if (actor->Position() == otherActor->Position())
			{
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					searchedActor = otherActor;
					break;
				}
			}
		}

		if (searchedActor)
		{
			continue;
		}

		actor->Render();
	}
}
void Level::SortActorsBySortingOrder()
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
