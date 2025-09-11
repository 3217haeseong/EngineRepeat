#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"

class Level;
class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor,RTTI)

public:
	Actor(
		const char* image = "",
		Color color = Color::White,
		const Vector2& position = Vector2::Zero
	);

	virtual ~Actor();
};