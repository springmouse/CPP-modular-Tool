#pragma once

#include "GameLoop.h"

void main()
{
	GameLoop * gm = new GameLoop();

	gm->GameLoopFunction();

	return;
}