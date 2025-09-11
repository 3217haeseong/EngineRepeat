#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"

#include <Windows.h>
#include <iostream>

Actor::Actor(const char* image, Color color, const Vector2& position)
	: color(color), position(position)
{
	width = (int)strlen(image);

	this->image = new char[width + 1];

	strcpy_s(this->image, width + 1, image);
}

Actor::~Actor()
{
	SafeDeleteArray(image);
}

void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

void Actor::Tick(float deltaTime)
{

}

void Actor::Render()
{
	Engine::Get().WriteToBuffer(position, image, color);
}

void Actor::SetPosition(const Vector2& newPosition)
{
	if (position == newPosition)
	{
		return;
	}

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

int Actor::Width() const
{
	return width;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

bool Actor::TestIntersect(const Actor* const other)
{
	int xMin = position.x;
	int xMax = position.x + width - 1;

	int otherXMin = other->position.x;
	int otherXMax = other->position.x + other->width - 1;

	if (otherXMin > xMax)
	{
		return false;
	}

	if (otherXMax < xMin)
	{
		return false;
	}

	return position.y == other->position.y;
}

void Actor::ChangeImage(const char* newImage)
{
	SafeDelete(image);

	size_t length = strlen(newImage) + 1;
	image = new char[length];
	strcpy_s(image, length, newImage);
}

void Actor::Destroy()
{
	if (isExpired)
	{
		return;
	}

	isExpired = true;

	owner->DestroyActor(this);

	OnDestroy();
}

void Actor::OnDestroy()
{
}

void Actor::SetLifetime(float newLifetime)
{
	if (newLifetime <= 0.0f)
	{
		return;
	}

	lifetime = newLifetime;

	autoDestroy = true;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}

