#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"

class Level;
class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(
		const char* image = "",
		Color color = Color::White,
		const Vector2& position = Vector2::Zero
	);

	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	inline bool HasBeganPlay() const { return hasBeganPlay; }

	void SetPosition(const Vector2& newPosition);
	Vector2 Position() const;

	int Width() const;

	void SetSortingOrder(unsigned int sortingOrder);

	void SetOwner(Level* newOwner);
	Level* GetOwner();

	bool TestIntersect(const Actor* const other);

	void ChangeImage(const char* newImage);

	void Destroy();

	virtual void OnDestroy();

	void SetLifetime(float newLifetime);

	void QuitGame();


protected:
	Vector2 position;

	char* image = nullptr;

	int width = 0;

	Color color;

	bool hasBeganPlay = false;

	unsigned int sortingOrder = 0;

	bool isActive = true;

	bool isExpired = false;

	float lifetime = 0.0f;

	bool autoDestroy = false;

	Level* owner = nullptr;
};