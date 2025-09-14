#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "RTTI.h"

enum class Color : int
{
	Blue = 1,
	Green = 2,
	Red =4 ,
	White = Red|Green | Blue,
	Intensity = 8,
};

class Level;
class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(
		const char image = ' ',
		Color color = Color::White,
		const Vector2 & position = Vector2::Zero
	);
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	inline bool HasBeganPlay() const { return hasBeganPlay; }

	void SetPosition(const Vector2& newPosition);
	Vector2 Position() const;

	void SetSortingOrder(unsigned int sortingOrder);

	void SetOwner(Level* newOwner);
	Level* GetOwner();

	void QuitGame();

private:
	Vector2 position;
	char image = ' ';
	Color color;
	bool hasBeganPlay = false;
	unsigned int sortingOrder = 0;
	Level* owner = nullptr;

};