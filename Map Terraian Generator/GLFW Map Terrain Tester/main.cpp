#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "GameManager.h"

int main()
{
	GameManager gameManager;

	gameManager.Init();

	gameManager.GameLoop();

	return 0;
}