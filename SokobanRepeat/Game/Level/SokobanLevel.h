#pragma once

#include "Level/Level.h"
#include "Interface/Interface.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel,Level)

public:
	SokobanLevel();

	virtual bool CanPlayerMove(
		const Vector2& playerPosition,
		const Vector2& newPosition) override;
	
private:
	virtual void Render() override;

private:
	void ReadMapFile(const char* filename);

	bool CheckGameClear();

	bool isGameClear = false;

private:
	int targetScore = 0;
	bool isGameClear = false;
};